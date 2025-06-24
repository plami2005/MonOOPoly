#pragma once
#include "Mortgage.h"

class Castle : public Mortgage {
public:
    int getRentBonus(int baseRent) const override;
    Mortgage* clone() const override;
    MortgageType getType() const override;
};