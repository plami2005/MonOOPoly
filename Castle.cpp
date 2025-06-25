#include "Castle.h"

int Castle::getRentBonus(int baseRent) const {
    double coef = 0.5;
    return (int)(baseRent * coef);
}

Mortgage* Castle::clone() const {
    return new Castle(*this);
}

MortgageType Castle::getType() const {
    return MortgageType::Castle;
}