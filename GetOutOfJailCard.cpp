#include "GetOutOfJailCard.h"
#include <iostream>
#include "Player.h"

GetOutOfJailCard::GetOutOfJailCard(const MyString& desc) : Card(desc) {}

void GetOutOfJailCard::applyEffect(Player& player) {
    std::cout << player.getName() << " receives a Get Out of Jail Free card.\n";
    player.giveJailCard();
}

Card* GetOutOfJailCard::clone() const {
    return new GetOutOfJailCard(*this);
}
