#pragma once
class Property;
class Player;

class Field {
public:
    virtual void onLand(Player& player) = 0;
    virtual ~Field() = default;
    virtual Property* asProperty() { return nullptr; }
};
