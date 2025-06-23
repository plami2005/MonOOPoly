#include "GoToFieldCard.h"
#include <iostream>
#include "Player.h"

GoToFieldCard::GoToFieldCard(int targetIndex, bool give200, const MyString& desc) : Card(desc), targetIndex(targetIndex), give200(give200) {}

void GoToFieldCard::applyEffect(Player& player) {
    int current = player.getPosition();
    player.move((targetIndex - current + 40) % 40);
    if (give200 && targetIndex < current) {
        std::cout << player.getName() << " passed GO and receives $200.\n";
        player.receive(200);
    }
    std::cout << player.getName() << " moves to field " << targetIndex << ".\n";
}

Card* GoToFieldCard::clone() const {
    return new GoToFieldCard(*this);
}