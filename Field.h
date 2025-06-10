#pragma once
#include "Player.h"

class Field {
    int index;
public:
    Field();
    Field(int index);
    virtual ~Field() = default;

    virtual void onLand(Player& player) = 0;
    int getIndex() const;
};
