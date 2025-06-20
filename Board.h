#pragma once
#include "Field.h"

class Board {
    Field** fields;
    int fieldCount;

public:
    Board(int size);
    ~Board();

    Field* getField(int index) const;
    int getSize() const;
};
