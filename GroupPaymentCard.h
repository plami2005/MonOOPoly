#pragma once
#include "Card.h"
#include "Player.h"

class GroupPaymentCard : public Card {
    int amount;
    Player** allPlayers;
    int playerCount;

public:
    GroupPaymentCard(int amount, Player** allPlayers, int playerCount);
    void applyEffect(Player& player) override;
    Card* clone() const override;
};
