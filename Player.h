#pragma once
#include "MyString.h"
#include "Board.h"
class Property;

class Player {
    MyString name;
    int balance;
    int position;
    bool inJail;
    int jailTurns;
    Property** ownedProperties;
    int propertyCount;
    int propertyCapacity;
    bool hasJailCard = false;
    bool liquidated = false;


    void resizeProperties();

public:
    Player();
    Player(const MyString& name);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();

    void move(int steps);
    bool pay(int amount);
    void receive(int amount);
    void goToJail();
    void leaveJail();
    bool isBankrupt() const;
    void buyProperty(Property* prop);

    const MyString& getName() const;
    int getBalance() const;
    int getPosition() const;
    bool getInJail() const;
    int getPropertyCount() const;
    Property* getPropertyAt(int index) const;
    void giveJailCard();
    bool useJailCard();
    bool ownsJailCard() const;
    void setPosition(int newPos);
    bool ownsAllOfColor(Color color, const Board* board) const;
    void printOwnedProperties() const;
    void addOwnedProperty(Property* p);
    void removeOwnedProperty(Property* p);
    void setJailTurns(int turns);
    int getJailTurns() const;
    bool isLiquidated() const;
    void liquidateAssets();
};