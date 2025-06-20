#include "CardField.h"
#include "CardDeck.h"
#include "Player.h"
#include <iostream>

CardField::CardField(CardDeck* deck) : deck(deck) {}

void CardField::onLand(Player& player) {
    std::cout << player.getName() << " landed on a Card Field.\n";
    deck->drawCard()->applyEffect(player);
}
