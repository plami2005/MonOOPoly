#pragma once
#include "Card.h"

class GetOutOfJailCard : public Card {
public:
    GetOutOfJailCard(const MyString& desc);
public:
    void applyEffect(Player& player) override;
    Card* clone() const override;
};