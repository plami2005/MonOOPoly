#include "PaymentCard.h"
#include <iostream>

PaymentCard::PaymentCard(int amount, const MyString& desc) : Card(desc), amount(amount) {}

void PaymentCard::applyEffect(Player& player) {
    if (amount >= 0) {
        std::cout << player.getName() << " receives $" << amount << ".\n";
        player.receive(amount);
    }
    else {
        std::cout << player.getName() << " pays $" << -amount << ".\n";
        player.pay(-amount);
    }
}

Card* PaymentCard::clone() const {
    return new PaymentCard(*this);
}
