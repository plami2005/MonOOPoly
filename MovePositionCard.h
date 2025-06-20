#pragma once
#include "Card.h"

class MovePositionCard : public Card {
    int offset;

public:
    MovePositionCard(int offset);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};