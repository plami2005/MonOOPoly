#pragma once
#include "Card.h"

class PaymentCard : public Card {
    int amount;

public:
    PaymentCard(int amount, const MyString& desc);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};