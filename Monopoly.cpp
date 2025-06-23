#include "Monopoly.h"
#include "Property.h"
#include "MovePositionCard.h"
#include "PaymentCard.h"
#include "GroupPaymentCard.h"
#include "GoToFieldCard.h"
#include "GetOutOfJailCard.h"
#include "Color.h"
#include <iostream>

Monopoly::Monopoly(int playerCount) : playerCount(playerCount), currentPlayerIndex(0) {
    players = new Player * [playerCount];
    for (int i = 0; i < playerCount; ++i) {
        MyString name;
        std::cout << "Enter name for player " << (i + 1) << ": ";
        std::cin >> name;
        players[i] = new Player(name);
    }

    board = new Board(40);

    // Special & fixed fields
    board->setField(0, nullptr); // Go
    board->setField(2, new CardField(&cardDeck)); // Community Chest
    board->setField(4, new Property("Income Tax", 200, 0, Color::Tax));
    board->setField(7, new CardField(&cardDeck)); // Chance
    board->setField(10, nullptr); // Jail / Just visiting
    board->setField(17, new CardField(&cardDeck)); // Community Chest
    board->setField(22, new CardField(&cardDeck)); // Chance
    board->setField(30, new GoToJailField());
    board->setField(33, new CardField(&cardDeck)); // Community Chest
    board->setField(36, new CardField(&cardDeck)); // Chance
    board->setField(38, new Property("Luxury Tax", 100, 0, Color::Tax));
    std::cout << "OK до 12\n";
    board->setField(12, new Property("Electric Company", 150, 0, Color::Utility));
    board->setField(28, new Property("Water Works", 150, 0, Color::Utility));


    // Properties
    board->setField(1, new Property("Mediterranean Avenue", 60, 2, Color::Brown));
    board->setField(3, new Property("Baltic Avenue", 60, 4, Color::Brown));
    board->setField(5, new Property("Reading Railroad", 200, 25, Color::Railroad));
    board->setField(6, new Property("Oriental Avenue", 100, 6, Color::LightBlue));
    board->setField(8, new Property("Vermont Avenue", 100, 6, Color::LightBlue));
    board->setField(9, new Property("Connecticut Avenue", 120, 8, Color::LightBlue));
    board->setField(11, new Property("St. Charles Place", 140, 10, Color::Pink));
    board->setField(13, new Property("States Avenue", 140, 10, Color::Pink));
    board->setField(14, new Property("Virginia Avenue", 160, 12, Color::Pink));
    board->setField(15, new Property("Pennsylvania Railroad", 200, 25, Color::Railroad));
    board->setField(16, new Property("St. James Place", 180, 14, Color::Orange));
    board->setField(18, new Property("Tennessee Avenue", 180, 14, Color::Orange));
    board->setField(20, new Property("New York Avenue", 200, 16, Color::Orange));
    board->setField(21, new Property("Kentucky Avenue", 220, 18, Color::Red));
    board->setField(23, new Property("Indiana Avenue", 220, 18, Color::Red));
    board->setField(24, new Property("Illinois Avenue", 240, 20, Color::Red));
    board->setField(25, new Property("B&O Railroad", 200, 25, Color::Railroad));
    board->setField(26, new Property("Atlantic Avenue", 260, 22, Color::Yellow));
    board->setField(27, new Property("Ventnor Avenue", 260, 22, Color::Yellow));
    board->setField(29, new Property("Marvin Gardens", 280, 24, Color::Yellow));
    board->setField(31, new Property("Pacific Avenue", 300, 26, Color::Green));
    board->setField(32, new Property("North Carolina Avenue", 300, 26, Color::Green));
    board->setField(34, new Property("Pennsylvania Avenue", 320, 28, Color::Green));
    board->setField(35, new Property("Short Line", 200, 25, Color::Railroad));
    board->setField(37, new Property("Park Place", 350, 35, Color::DarkBlue));
    board->setField(39, new Property("Boardwalk", 400, 50, Color::DarkBlue));

    CardDeck cardDeck;
    // Initialize 20 cards in the deck (10 Chance + 10 Community Chest)
    cardDeck.addCard(new GoToFieldCard(0, false, "Go to GO"));
    cardDeck.addCard(new GoToFieldCard(10, false, "Go to Jail"));
    cardDeck.addCard(new GoToFieldCard(24, true, "Go to Illinois Avenue. Collect $200 if you pass GO."));
    cardDeck.addCard(new GoToFieldCard(11, true, "Go to St. Charles Place. Collect $200 if you pass GO."));
    cardDeck.addCard(new MovePositionCard(-3, "Move back 3 spaces"));
    cardDeck.addCard(new PaymentCard(50, "Receive $50 from the bank"));
    cardDeck.addCard(new PaymentCard(-15, "Pay $15 fine for speeding"));
    cardDeck.addCard(new GetOutOfJailCard("Get Out of Jail Free Ц Keep or sell"));
    cardDeck.addCard(new PaymentCard(200, "Collect $200 for passing GO"));
    cardDeck.addCard(new PaymentCard(100, "You inherit $100"));
    cardDeck.addCard(new PaymentCard(20, "Tax refund. Collect $20"));
    cardDeck.addCard(new PaymentCard(-100, "Pay hospital bill of $100"));
    cardDeck.addCard(new PaymentCard(-150, "Pay school fees of $150"));
    cardDeck.addCard(new PaymentCard(200, "Bank error in your favor. Collect $200"));
    cardDeck.addCard(new PaymentCard(50, "Receive $50 dividend"));
    cardDeck.addCard(new PaymentCard(-100, "Donate $100 to charity"));
    cardDeck.addCard(new GroupPaymentCard(10, players, playerCount, "Collect $10 from each player"));
    cardDeck.addCard(new GroupPaymentCard(-10, players, playerCount, "Pay $10 to each player"));
    cardDeck.addCard(new GetOutOfJailCard("Another Get Out of Jail Free card"));

}

Monopoly::~Monopoly() {
    for (int i = 0; i < playerCount; ++i)
        delete players[i];
    delete[] players;
    delete board;
}

void Monopoly::startGame() {
    std::cout << "Game started with " << playerCount << " players.\n";
    while (!isGameOver()) {
        printGameState();
        playTurn();
        currentPlayerIndex = (currentPlayerIndex + 1) % playerCount;
    }
    std::cout << "Game over! Winner: " << players[currentPlayerIndex]->getName() << "\n";
}

void Monopoly::playTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    std::cout << "\n" << currentPlayer->getName() << "'s turn.\n";
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int steps = dice1 + dice2;
    std::cout << "Rolled: " << dice1 << "+" << dice2 << " = " << steps << "\n";

    if (currentPlayer->getInJail()) {
        std::cout << "Player is in jail and skips turn.\n";
        currentPlayer->leaveJail();
        return;
    }

    int oldPos = currentPlayer->getPosition();
    currentPlayer->move(steps);
    int newPos = currentPlayer->getPosition();
    if (newPos < oldPos) {
        std::cout << currentPlayer->getName() << " passed Start and receives $200. ";
            bank.giveMoney(*currentPlayer, 200);
    }
    Field* landed = board->getField(currentPlayer->getPosition());
    if (landed)
        landed->onLand(*currentPlayer);
}

bool Monopoly::isGameOver() const {
    int activePlayers = 0;
    for (int i = 0; i < playerCount; ++i) {
        if (!players[i]->isBankrupt())
            ++activePlayers;
    }
    return activePlayers <= 1;
}

void Monopoly::printGameState() const {
    std::cout << "\nCurrent game state:\n";
    for (int i = 0; i < playerCount; ++i) {
        std::cout << players[i]->getName() << " - Balance: $" << players[i]->getBalance();
        if (players[i]->getInJail()) std::cout << " (In Jail)";
        std::cout << "\n";
    }
}

Board* Monopoly::getBoard() const {
    return board;
}

