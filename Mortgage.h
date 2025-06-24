#pragma once

enum class MortgageType {
    Cottage,
    Castle
};

class Mortgage {
public:
    virtual int getRentBonus(int baseRent) const = 0;
    virtual Mortgage* clone() const = 0;
    virtual ~Mortgage() = default;
    virtual MortgageType getType() const = 0;
};