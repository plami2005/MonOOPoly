#pragma once
#include "Card.h"

class GoToFieldCard : public Card {
    int targetIndex;
    bool give200;

public:
    GoToFieldCard(int targetIndex, bool give200, const MyString& desc);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};
