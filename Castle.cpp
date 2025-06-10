#include "Castle.h"

int Castle::modifyRent(int baseRent) const {
    return baseRent + (baseRent * 50) / 100;
}
