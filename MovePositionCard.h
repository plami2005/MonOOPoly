#pragma once
#include "Card.h"

class MovePositionCard : public Card {
    int offset;

public:
    MovePositionCard(int offset, const MyString& desc);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};
