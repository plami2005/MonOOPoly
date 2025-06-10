#include "Cottage.h"

int Cottage::modifyRent(int baseRent) const {
    return baseRent + (baseRent * 15) / 100;
}
