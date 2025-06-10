#pragma once
#include "Mortgage.h"
#include "MyString.h"
#include "Field.h"

class Property : public Field {
private:
    MyString name;
    int price;
    int baseRent;
    Mortgage* mortgage;
    bool isCastle;

    void copyFrom(const Property& other);
    void free();

public:
    Property(const MyString& name, int price, int rent);
    Property(const Property& other);
    Property& operator=(const Property& other);
    ~Property();

    Property(Property&& other);
    Property& operator=(Property&& other);

    const MyString& getName() const;
    int getRent() const;
    int getPrice() const;

    void upgradeToCottage();
    void upgradeToCastle();
    bool hasMortgage() const;
    bool isUpgradedToCastle() const;

    void onLand(Player& player) override;
};
