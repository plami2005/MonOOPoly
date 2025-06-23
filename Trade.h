#pragma once
#include "Player.h"
#include "Property.h"

class Trade {
    Player* from;
    Player* to;
    Property* offeredProperty;
    Property* requestedProperty;
    int moneyFromFrom;
    int moneyFromTo;

public:
    Trade(Player* from, Player* to);

    void offerProperty(Property* property);
    void requestProperty(Property* property);
    void offerMoney(int amount);
    void requestMoney(int amount);

    bool execute();
};
