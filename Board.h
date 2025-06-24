#pragma once
#include "Field.h"
#include "MyVector.hpp"
#include "Property.h"

class Board {
    Field** fields;
    int fieldCount;
    MyVector<Property*> allProperties;

public:
    Board(int size);
    ~Board();

    void setField(int index, Field* field);
    Field* getField(int index) const;
    int getSize() const;
    void registerProperty(Property* p);
    const MyVector<Property*>& getAllProperties() const;
    void offerBuildingOptions(Player* player);
    void handleLanding(Player* player);
    // В началото на Board.cpp
    Property* tryConvertToProperty(Field* field);

};
