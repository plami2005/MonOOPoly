#include "CardField.h"
#include "CardDeck.h"
#include "Player.h"
#include <iostream>

CardField::CardField(CardDeck* deck) : deck(deck) {}

void CardField::onLand(Player& player) {
    std::cout << player.getName() << " landed on a Card Field.\n";
    Card* card = deck->drawCard();
    if (card) {
        card->applyEffect(player);
        deck->returnCardToBottom(card);
    }
}
