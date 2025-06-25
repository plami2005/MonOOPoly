#include "Monopoly.h"
#include "Property.h"
#include "MovePositionCard.h"
#include "PaymentCard.h"
#include "GroupPaymentCard.h"
#include "GoToFieldCard.h"
#include "MyVector.hpp"
#include "GetOutOfJailCard.h"

#include <iostream>

void Monopoly::free()
{
	for (size_t i = 0; i < playerCount; i++)
	{
		delete players[i];
		players[i] = nullptr;
	}
	delete[] players;
	playerCount = 0;
	currentPlayerIndex = 0;
	delete board;
	bank = Bank();
	cardDeck = CardDeck();
}

void Monopoly::copyFrom(const Monopoly& other)
{
	players = new Player * [other.playerCount];
	playerCount = other.playerCount;
	for (size_t i = 0; i < playerCount; i++)
	{
		players[i] = new Player(*other.players[i]);
	}
	currentPlayerIndex = other.currentPlayerIndex;
	board = new Board(*board);
	bank = other.bank;
	cardDeck = other.cardDeck;
}

void Monopoly::moveFrom(Monopoly&& other)
{
	players = other.players;
	playerCount = other.playerCount;
	currentPlayerIndex = other.currentPlayerIndex;
	board = other.board;
	bank = other.bank;
	cardDeck = other.cardDeck;

	other.players = nullptr;
	other.board = nullptr;
}

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
	board->setField(4, new Property("Income Tax", 200, 200, Color::Tax));
	board->setField(7, new CardField(&cardDeck)); // Chance
	board->setField(10, nullptr); // Jail / Just visiting
	board->setField(17, new CardField(&cardDeck)); // Community Chest
	board->setField(19, nullptr);// Parking
	board->setField(22, new CardField(&cardDeck)); // Chance
	board->setField(30, new GoToJailField());
	board->setField(33, new CardField(&cardDeck)); // Community Chest
	board->setField(36, new CardField(&cardDeck)); // Chance
	board->setField(38, new Property("Luxury Tax", 100, 100, Color::Tax));
	board->setField(12, new Property("Electric Company", 150, 50, Color::Utility));
	board->setField(28, new Property("Water Works", 150, 50, Color::Utility));


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

	// Initialize 20 cards in the deck (10 Chance + 10 Community Chest)
	cardDeck.addCard(new GoToFieldCard(0, false, "Go to GO"));
	cardDeck.addCard(new GoToFieldCard(10, false, "Go to Jail"));
	cardDeck.addCard(new GoToFieldCard(24, true, "Go to Illinois Avenue. Collect $200 if you pass GO."));
	cardDeck.addCard(new GoToFieldCard(11, true, "Go to St. Charles Place. Collect $200 if you pass GO."));
	cardDeck.addCard(new MovePositionCard(-3, "Move back 3 spaces"));
	cardDeck.addCard(new PaymentCard(50, "Receive $50 from the bank"));
	cardDeck.addCard(new PaymentCard(-15, "Pay $15 fine for speeding"));
	cardDeck.addCard(new GetOutOfJailCard("Get Out of Jail Free – Keep or sell"));
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
	std::cout << "All cards added successfully to deck.\n";

}

Monopoly::Monopoly(const Monopoly& other)
{
	copyFrom(other);
}

Monopoly::Monopoly(Monopoly&& other) noexcept
{
	moveFrom(std::move(other));
}

Monopoly& Monopoly::operator=(const Monopoly& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Monopoly& Monopoly::operator=(Monopoly&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Monopoly::~Monopoly() {
	free();
}

Player* Monopoly::getWinner() const {
	for (int i = 0; i < playerCount; ++i) {
		if (!players[i]->isBankrupt())
			return players[i];
	}
	return nullptr;
}

void Monopoly::startGame() {
	std::cout << "Game started with " << playerCount << " players.\n";

	while (!isGameOver()) {
		printGameState();

		bool repeatTurn;
		do {
			repeatTurn = playTurn();
		} while (repeatTurn);

		currentPlayerIndex = (currentPlayerIndex + 1) % playerCount;
		while (players[currentPlayerIndex]->isBankrupt()) {
			currentPlayerIndex = (currentPlayerIndex + 1) % playerCount;
		}
	}

	Player* winner = getWinner();
	if (winner)
		std::cout << "\n Game over! The winner is " << winner->getName().c_str()
		<< " with $" << winner->getBalance() << "!\n";
	else
		std::cout << "\nNo winner found.\n";
}
bool Monopoly::playTurn() {
	Player* currentPlayer = players[currentPlayerIndex];

	if (currentPlayer->isBankrupt()) {
		return false;
	}

	std::cout << "\n" << currentPlayer->getName() << "'s turn.\n";

	if (currentPlayer->getInJail()) {
		std::cout << "Player is in jail.\n";

		if (currentPlayer->ownsJailCard()) {
			std::cout << "Using 'Get Out of Jail Free' card.\n";
			currentPlayer->useJailCard();
		}
		else {
			int d1 = rand() % 6 + 1;
			int d2 = rand() % 6 + 1;
			std::cout << "Rolled: " << d1 << "+" << d2 << "\n";
			if (d1 == d2) {
				std::cout << "Double rolled! Released from jail.\n";
				currentPlayer->leaveJail();
			}
			else if (currentPlayer->getJailTurns() >= 2)
			{
				currentPlayer->pay(100);
				std::cout << "Payed 100$ to get out of jail!";
				currentPlayer->leaveJail();
			}
			else {
				std::cout << "Still in jail.\n";
				currentPlayer->setJailTurns(currentPlayer->getJailTurns() + 1);
				return false;
			}
		}
	}

	bool turnEnded = false;
	bool rolled = false;

	int dice1 = 0, dice2 = 0, steps = 0;
	int oldPos = 0, newPos = 0;
	int choice = 0;
	int cntRolls = 0;


	while (!turnEnded) {
		std::cout << "\nChoose an option:\n";
		std::cout << "1. Roll dice\n";
		std::cout << "2. View properties\n";
		std::cout << "3. Build on property\n";
		std::cout << "4. Show player info\n";
		std::cout << "5. Buy property from another player\n";
		std::cout << "Your choice: ";

		choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			if (rolled) {
				if (cntRolls >= 3)
				{
					std::cout << "You've already rolled this turn.\n";
					break;
				}
			}

			dice1 = rand() % 6 + 1;
			dice2 = rand() % 6 + 1;
			steps = dice1 + dice2;

			std::cout << "Rolled: " << dice1 << " + " << dice2 << " = " << steps << "\n";

			oldPos = currentPlayer->getPosition();
			currentPlayer->move(steps);
			newPos = currentPlayer->getPosition();

			if (newPos < oldPos) {
				std::cout << currentPlayer->getName() << " passed GO. Collects $200.\n";
				bank.giveMoney(*currentPlayer, 200);
			}

			board->handleLanding(currentPlayer);
			board->offerBuildingOptions(currentPlayer);

			rolled = true;
			cntRolls++;
			if (dice1 != dice2) turnEnded = true;
			break;

		case 2:
			currentPlayer->printOwnedProperties();
			break;

		case 3:
			board->offerBuildingOptions(currentPlayer);
			break;

		case 4:
			std::cout << "\n--- Player Info ---\n";
			std::cout << "Name: " << currentPlayer->getName() << "\n";
			std::cout << "Balance: $" << currentPlayer->getBalance() << "\n";
			std::cout << "Position: " << currentPlayer->getPosition() << "\n";
			std::cout << (currentPlayer->getInJail() ? "Status: In Jail\n" : "Status: Free\n");
			std::cout << "Owned properties:\n";
			currentPlayer->printOwnedProperties();
			break;
		case 5: {
			int sellerIndex = -1;
			std::cout << "Select seller:\n";
			for (int i = 0; i < playerCount; ++i) {
				if (i != currentPlayerIndex && !players[i]->isBankrupt()) {
					std::cout << i << ". " << players[i]->getName().c_str() << "\n";
				}
			}
			std::cin >> sellerIndex;

			if (sellerIndex < 0 || sellerIndex >= playerCount || sellerIndex == currentPlayerIndex || players[sellerIndex]->isBankrupt()) {
				std::cout << "Invalid selection.\n";
				break;
			}

			Player* seller = players[sellerIndex];
			seller->printOwnedProperties();

			int propertyIndex = -1;
			std::cout << "Enter index of property to offer: ";
			std::cin >> propertyIndex;

			Property* prop = seller->getPropertyAt(propertyIndex);
			if (!prop) {
				std::cout << "Invalid property.\n";
				break;
			}

			std::cout << "Enter amount to offer: $";
			int offer;
			std::cin >> offer;

			std::cout << seller->getName().c_str() << ", do you accept the offer of $" << offer << " for "
				<< prop->getName().c_str() << "? (y/n): ";
			char response;
			std::cin >> response;

			if (response == 'y' || response == 'Y') {
				if (currentPlayer->getBalance() >= offer) {
					currentPlayer->pay(offer);
					seller->receive(offer);
					prop->setOwner(currentPlayer);
					currentPlayer->addOwnedProperty(prop);
					seller->removeOwnedProperty(prop);
					std::cout << "Transaction complete.\n";
				}
				else {
					std::cout << "Not enough money to complete transaction.\n";
				}
			}
			else {
				std::cout << "Seller declined the offer.\n";
			}
			break;
		}
		default:
			std::cout << "Invalid choice.\n";
		}
	}

	if (currentPlayer->isBankrupt() && !currentPlayer->isLiquidated()) {
		currentPlayer->liquidateAssets();
		std::cout << currentPlayer->getName() << " was eliminated from the game (went bankrupt)!";
		return false;
	}

	std::cout << "End of turn. Current balance: $" << currentPlayer->getBalance() << "\n";
	return false;
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

void Monopoly::printCardDeck() const {
	std::cout << "\n--- CARD DECK CONTENTS ---\n";
	cardDeck.printContents();
}
