#pragma once
#include "Card.h"
#include "Player.h"

class GroupPaymentCard : public Card {
    int amount;
    Player** allPlayers;
    int playerCount;

public:
    GroupPaymentCard(int amount, Player** allPlayers, int playerCount, const MyString& desc);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};