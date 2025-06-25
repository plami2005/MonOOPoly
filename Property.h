#pragma once
#include "Field.h"
#include "MyString.h"
#include "Mortgage.h"


class Player;

enum class Color {
    Brown,
    LightBlue,
    Pink,
    Orange,
    Red,
    Yellow,
    Green,
    DarkBlue,
    Railroad,
    Utility,
    Tax,
    None
};

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
    void removeOwnership();

    const MyString& getName() const;
    int getPrice() const;
    int getBaseRent() const;
    Color getColor() const;
    Property* asProperty() override { return this; }
    int getMortgageCount() const { return mortgageCount; }
    Mortgage* getMortgageAt(int i) const { return mortgages[i]; }
    bool isProperty() const override { return true; }

    virtual Field* clone() const override;
};