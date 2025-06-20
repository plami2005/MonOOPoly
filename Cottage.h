#pragma once
#include "Mortgage.h"

class Cottage : public Mortgage {
public:
    int getRentBonus(int baseRent) const override;
    Mortgage* clone() const override;
};
