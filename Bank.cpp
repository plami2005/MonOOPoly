#include "Bank.h"

void Bank::giveMoney(Player& player, int amount) {
    player.receive(amount);
}

bool Bank::takeMoney(Player& player, int amount) {
    return player.pay(amount);
}