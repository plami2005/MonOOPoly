#pragma once

class Mortgage {
public:
    virtual int modifyRent(int baseRent) const = 0;
    virtual ~Mortgage() {}
};