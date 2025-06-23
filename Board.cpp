#include "Board.h"

Board::Board(int size) : fieldCount(size) {
    fields = new Field * [fieldCount] {};
}

Board::~Board() {
    for (int i = 0; i < fieldCount; ++i)
        delete fields[i];
    delete[] fields;
}

void Board::setField(int index, Field* field) {
    if (index >= 0 && index < fieldCount)
        fields[index] = field;
}

Field* Board::getField(int index) const {
    if (index < 0 || index >= fieldCount)
        return nullptr;
    return fields[index];
}

int Board::getSize() const { return fieldCount; }