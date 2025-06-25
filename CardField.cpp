#include "CardField.h"
#include "CardDeck.h"
#include "Player.h"
#include <iostream>

CardField::CardField(CardDeck* deck) : deck(deck) {}

void CardField::onLand(Player& player) {
    std::cout << player.getName() << " landed on a Card Field.\n";
    Card* card = deck->drawCard();
    if (card) {
        std::cout << "Card drawn: " << card->getDescription().c_str() << "\n";
        card->applyEffect(player);
        deck->returnCardToBottom(card);
    }
}

Field* CardField::clone() const
{
    return new CardField(*this);
}
