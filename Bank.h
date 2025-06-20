#pragma once
#include "Player.h"

class Bank {
public:
    void giveMoney(Player& player, int amount);
    bool takeMoney(Player& player, int amount);
};