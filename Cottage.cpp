#include "Cottage.h"

int Cottage::getRentBonus(int baseRent) const {
    double coef = 0.15;
    return (int)(baseRent * coef);
}

Mortgage* Cottage::clone() const {
    return new Cottage(*this);
}

MortgageType Cottage::getType() const {
    return MortgageType::Cottage;
}
