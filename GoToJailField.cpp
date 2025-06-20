#include "GoToJailField.h"
#include "Player.h"
#include <iostream>

void GoToJailField::onLand(Player& player) {
    std::cout << player.getName() << " is sent directly to jail!\n";
    player.goToJail();
}
