#include "Trade.h"
#include <iostream>

Trade::Trade(Player* from, Player* to)
    : from(from), to(to), offeredProperty(nullptr), requestedProperty(nullptr), moneyFromFrom(0), moneyFromTo(0) {}

void Trade::offerProperty(Property* property) {
    offeredProperty = property;
}

void Trade::requestProperty(Property* property) {
    requestedProperty = property;
}

void Trade::offerMoney(int amount) {
    moneyFromFrom = amount;
}

void Trade::requestMoney(int amount) {
    moneyFromTo = amount;
}

bool Trade::execute() {
    if (offeredProperty && offeredProperty->getOwner() != from) {
        std::cout << "Trade failed: " << from->getName() << " does not own " << offeredProperty->getName() << ".\n";
        return false;
    }
    if (requestedProperty && requestedProperty->getOwner() != to) {
        std::cout << "Trade failed: " << to->getName() << " does not own " << requestedProperty->getName() << ".\n";
        return false;
    }
    if (!from->pay(moneyFromFrom) || !to->pay(moneyFromTo)) {
        std::cout << "Trade failed: insufficient funds.\n";
        return false;
    }

    to->receive(moneyFromFrom);
    from->receive(moneyFromTo);

    if (offeredProperty) {
        offeredProperty->setOwner(to);
        to->buyProperty(offeredProperty);
    }
    if (requestedProperty) {
        requestedProperty->setOwner(from);
        from->buyProperty(requestedProperty);
    }

    std::cout << "Trade successful between " << from->getName() << " and " << to->getName() << ".\n";
    return true;
}
