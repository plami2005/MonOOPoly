#include "Castle.h"

int Castle::getRentBonus(int baseRent) const {
    return baseRent * 50 / 100;
}

Mortgage* Castle::clone() const {
    return new Castle(*this);
}
