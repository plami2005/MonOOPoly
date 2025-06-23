#include "MovePositionCard.h"
#include <iostream>
#include "Player.h"

MovePositionCard::MovePositionCard(int offset, const MyString& desc)
    : Card(desc), offset(offset) {}

void MovePositionCard::applyEffect(Player& player) {
    std::cout << getDescription() << "\n";
    player.move(offset);
}

Card* MovePositionCard::clone() const {
    return new MovePositionCard(*this);
}
