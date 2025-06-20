#pragma once
#include "Player.h"

class Card {
public:
    virtual void applyEffect(Player& player) = 0;
    virtual Card* clone() const = 0;
    virtual ~Card() = default;
};
