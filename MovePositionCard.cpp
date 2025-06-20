#include "MovePositionCard.h"
#include <iostream>

MovePositionCard::MovePositionCard(int offset) : offset(offset) {}

void MovePositionCard::applyEffect(Player& player) {
    std::cout << player.getName() << " moves " << offset << " steps.\n";
    player.move(offset);
}

Card* MovePositionCard::clone() const {
    return new MovePositionCard(*this);
}