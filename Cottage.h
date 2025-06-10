#pragma once
#include "Mortgage.h"

class Cottage : public Mortgage {
public:
    int modifyRent(int baseRent) const override;
};