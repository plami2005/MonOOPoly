#pragma once
#include "Mortgage.h"

class Castle : public Mortgage {
public:
    int modifyRent(int baseRent) const override;
};