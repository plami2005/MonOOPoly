#pragma once
#include "Field.h"
#include "MyString.h"
#include "Mortgage.h"
#include "Color.h"

class Player;

class Property : public Field {
    MyString name;
    int price;
    int baseRent;
    Player* owner;
    Mortgage** mortgages;
    int mortgageCount;
    int mortgageCapacity;
    Color color;

    void resizeMortgages();

public:
    Property();
    Property(const MyString& name, int price, int baseRent, Color color);
    Property(const Property& other);
    Property& operator=(const Property& other);
    ~Property();

    void onLand(Player& player) override;
    void buildCottage();
    void buildCastle();

    int calculateRent() const;
    Player* getOwner() const;
    void setOwner(Player* newOwner);

    const MyString& getName() const;
    int getPrice() const;
    int getBaseRent() const;
    Color getColor() const;
    
};