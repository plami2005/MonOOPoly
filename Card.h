#pragma once
#include "Player.h"
#include "MyString.h"

class Card {
protected:
    MyString description;

public:
    Card(const MyString& desc) : description(desc) {}
    virtual void applyEffect(Player& player) = 0;
    virtual Card* clone() const = 0;
    virtual const MyString& getDescription() const { return description; }
    virtual ~Card() = default;
};