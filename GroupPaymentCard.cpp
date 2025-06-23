#include "GroupPaymentCard.h"
#include <iostream>

GroupPaymentCard::GroupPaymentCard(int amount, Player** allPlayers, int playerCount, const MyString& desc) 
    : Card(desc), amount(amount), allPlayers(allPlayers), playerCount(playerCount) {}

void GroupPaymentCard::applyEffect(Player& player) {
    if (amount >= 0) {
        int total = amount * (playerCount - 1);
        std::cout << player.getName() << " receives $" << amount << " from each player.\n";
        player.receive(total);
        for (int i = 0; i < playerCount; ++i) {
            if (allPlayers[i] != &player)
                allPlayers[i]->pay(amount);
        }
    }
    else {
        int payEach = -amount;
        std::cout << player.getName() << " pays $" << payEach << " to each player.\n";
        for (int i = 0; i < playerCount; ++i) {
            if (allPlayers[i] != &player) {
                if (player.pay(payEach))
                    allPlayers[i]->receive(payEach);
            }
        }
    }
}

Card* GroupPaymentCard::clone() const {
    return new GroupPaymentCard(*this);
}