#pragma once

class Player;

class Field {
public:
    virtual void onLand(Player& player) = 0;
    virtual ~Field() = default;
};
