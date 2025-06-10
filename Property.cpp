#include "Property.h"
#include "Cottage.h"
#include "Castle.h"
#include <cstring>
#include <iostream>

void Property::copyFrom(const Property& other) {
    name = other.name;
    price = other.price;
    baseRent = other.baseRent;
    isCastle = other.isCastle;

    mortgage = other.mortgage ? (isCastle ? new Castle() : new Cottage()) : nullptr;
}

void Property::free() {
    delete mortgage;
    mortgage = nullptr;
}

Property::Property(const MyString& _name, int _price, int _rent)
    : name(_name), price(_price), baseRent(_rent), mortgage(nullptr), isCastle(false) {}

Property::Property(const Property& other) {
    copyFrom(other);
}

Property& Property::operator=(const Property& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Property::~Property() {
    free();
}

Property::Property(Property&& other)
    : name(std::move(other.name)), price(other.price), baseRent(other.baseRent), mortgage(other.mortgage), isCastle(other.isCastle) {
    other.name = nullptr;
    other.mortgage = nullptr;
}

Property& Property::operator=(Property&& other) {
    if (this != &other) {
        free();
        name = std::move(other.name);
        price = other.price;
        baseRent = other.baseRent;
        mortgage = other.mortgage;
        isCastle = other.isCastle;

        other.mortgage = nullptr;
    }
    return *this;
}




const MyString& Property::getName() const {
    return name;
}

int Property::getRent() const {
    if (mortgage)
        return mortgage->modifyRent(baseRent);
    return baseRent;
}

int Property::getPrice() const {
    return price;
}


void Property::upgradeToCottage() {
    delete mortgage;
    mortgage = new Cottage();
    isCastle = false;
}

void Property::upgradeToCastle() {
    delete mortgage;
    mortgage = new Castle();
    isCastle = true;
}

bool Property::hasMortgage() const {
    return mortgage != nullptr;
}

bool Property::isUpgradedToCastle() const {
    return isCastle;
}