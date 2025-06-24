#include "Player.h"
#include "Property.h"
#include "MyVector.hpp"
#include <iostream>

void Player::resizeProperties() {
    int newCapacity = propertyCapacity * 2;
    if (newCapacity == 0) newCapacity = 4;
    Property** newArr = new Property * [newCapacity];
    for (int i = 0; i < propertyCount; ++i)
        newArr[i] = ownedProperties[i];
    delete[] ownedProperties;
    ownedProperties = newArr;
    propertyCapacity = newCapacity;
}

Player::Player() : name("Player"), balance(1500), position(0), inJail(false), jailTurns(0), ownedProperties(nullptr), propertyCount(0), propertyCapacity(0) {}

Player::Player(const MyString& name) : name(name), balance(1500), position(0), inJail(false), jailTurns(0), ownedProperties(nullptr), propertyCount(0), propertyCapacity(0) {}

Player::Player(const Player& other) : name(other.name), balance(other.balance), position(other.position), inJail(other.inJail), jailTurns(other.jailTurns), propertyCount(other.propertyCount), propertyCapacity(other.propertyCapacity) {
    ownedProperties = new Property * [propertyCapacity];
    for (int i = 0; i < propertyCount; ++i)
        ownedProperties[i] = other.ownedProperties[i];
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        delete[] ownedProperties;
        name = other.name;
        balance = other.balance;
        position = other.position;
        inJail = other.inJail;
        jailTurns = other.jailTurns;
        propertyCount = other.propertyCount;
        propertyCapacity = other.propertyCapacity;
        ownedProperties = new Property * [propertyCapacity];
        for (int i = 0; i < propertyCount; ++i)
            ownedProperties[i] = other.ownedProperties[i];
    }
    return *this;
}

Player::~Player() {
    delete[] ownedProperties;
}

void Player::move(int steps) {
    position = (position + steps) % 40; // 40 fields
}

bool Player::pay(int amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void Player::receive(int amount) {
    balance += amount;
}

void Player::goToJail() {
    inJail = true;
    jailTurns = 0;
    position = 10; // jail 
}

void Player::leaveJail() {
    inJail = false;
    jailTurns = 0;
}

bool Player::isBankrupt() const {
    return balance < 0;
}

void Player::bankrupt() {
    bankruptFlag = true;
    balance = 0;
}

void Player::buyProperty(Property* prop) {
    if (propertyCount >= propertyCapacity)
        resizeProperties();
    ownedProperties[propertyCount++] = prop;
}

const MyString& Player::getName() const { return name; }
int Player::getBalance() const { return balance; }
int Player::getPosition() const { return position; }
bool Player::getInJail() const { return inJail; }
int Player::getPropertyCount() const { return propertyCount; }

Property* Player::getPropertyAt(int index) const {
    if (index < 0 || index >= propertyCount)
        return nullptr;
    return ownedProperties[index];
}

void Player::giveJailCard() {
    hasJailCard = true;
}

bool Player::ownsJailCard() const {
    return hasJailCard;
}

bool Player::useJailCard() {
    if (hasJailCard) {
        hasJailCard = false;
        return true;
    }
    return false;
}

void Player::setPosition(int newPos) {
    position = newPos % 40;
}

bool Player::ownsAllOfColor(Color color, const Board* board) const {
    const MyVector<Property*>& allProps = board->getAllProperties();
    for (size_t i = 0; i < allProps.size(); ++i) {
        if (allProps[i]->getColor() == color && allProps[i]->getOwner() != this)
            return false;
    }
    return true;
}

void Player::printOwnedProperties() const {
    std::cout << getName() << "'s properties:\n";
    for (int i = 0; i < propertyCount; ++i) {
        std::cout << "- " << ownedProperties[i]->getName().c_str() << " ($" << ownedProperties[i]->getPrice() << ")\n";
    }
    if (propertyCount == 0)
        std::cout << "(none)\n";
}


void Player::addOwnedProperty(Property* p) {
    if (propertyCount >= propertyCapacity) {
        int newCapacity = propertyCapacity * 2;
        if (newCapacity == 0) newCapacity = 4;
        Property** newArr = new Property * [newCapacity];
        for (int i = 0; i < propertyCount; ++i)
            newArr[i] = ownedProperties[i];
        delete[] ownedProperties;
        ownedProperties = newArr;
        propertyCapacity = newCapacity;
    }
    ownedProperties[propertyCount++] = p;
}

void Player::removeOwnedProperty(Property* p) {
    for (int i = 0; i < propertyCount; ++i) {
        if (ownedProperties[i] == p) {
            for (int j = i; j < propertyCount - 1; ++j)
                ownedProperties[j] = ownedProperties[j + 1];
            --propertyCount;
            break;
        }
    }
}
