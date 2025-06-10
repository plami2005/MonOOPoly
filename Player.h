#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Property.h"
#include "Field.h"
#include <fstream>

class Player {
private:
    int playerId;
    MyString name;
    int balance;
    int position;
    bool inJail;
    int jailTurns;
    int pairsCount;
    Field* current;
    MyVector<Property*> properties;

public:
    Player();
    Player(int playerId, const MyString& name, int balance);

    void move(int steps);
    void pay(int amount);
    void receive(int amount);
    void goToJail();
    void leaveJail();
    bool isBankrupt() const;

    int getPlayerId() const;
    const MyString& getName() const;
    int getBalance() const;
    int getPosition() const;
    int getPairsCount() const;
    bool isInJail() const;


    void addProperty(Property* property);
    void removeProperty(Property* property);
    const MyVector<Property*>& getProperties() const;

    void saveToBinary(std::ofstream& out) const;
    void loadFromBinary(std::ifstream& in);
};