#include "Cottage.h"

int Cottage::getRentBonus(int baseRent) const {
    return baseRent * 15 / 100;
}

Mortgage* Cottage::clone() const {
    return new Cottage(*this);
}
