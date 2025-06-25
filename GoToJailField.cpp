#include "GoToJailField.h"
#include "Player.h"
#include <iostream>

void GoToJailField::onLand(Player& player) {
    std::cout << player.getName() << " landed on 'Go to Jail'.\n";
    if (player.ownsJailCard()) {
        std::cout << player.getName() << " uses a 'Get Out of Jail Free' card and stays at Just Visiting.\n";
        player.useJailCard();
        player.setPosition(10);
    }
    else {
        player.setPosition(10);
        player.goToJail(); 
    }
}

Field* GoToJailField::clone() const
{
    return new GoToJailField(*this);
}
