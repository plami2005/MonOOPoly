#pragma once
#include "Field.h"
#include "MyVector.hpp"
#include "Property.h"

class Board {
	Field** fields;
	int fieldCount;
	MyVector<Property*> allProperties;

	void free();
	void copyFrom(const Board& other);
	void moveFrom(Board&& other);

public:
	Board(int size);
	Board(const Board& board);
	Board(Board&& board) noexcept;
	Board& operator=(const Board& board);
	Board& operator=(Board&& board) noexcept;
	~Board();

	void setField(int index, Field* field);
	Field* getField(int index) const;
	int getSize() const;
	void registerProperty(Property* p);
	const MyVector<Property*>& getAllProperties() const;
	void offerBuildingOptions(Player* player);
	void handleLanding(Player* player);
	Property* tryConvertToProperty(Field* field);
};
