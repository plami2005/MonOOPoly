#include "Property.h"
#include "Player.h"
#include "Cottage.h"
#include "Castle.h"
#include <iostream>

void Property::resizeMortgages() {
    int newCap = mortgageCapacity * 2;
    if (newCap == 0) newCap = 4;
    Mortgage** newArr = new Mortgage * [newCap];
    for (int i = 0; i < mortgageCount; ++i)
        newArr[i] = mortgages[i]->clone();
    for (int i = 0; i < mortgageCount; ++i)
        delete mortgages[i];
    delete[] mortgages;
    mortgages = newArr;
    mortgageCapacity = newCap;
}

Property::Property() : name("Unnamed"), price(0), baseRent(0), owner(nullptr), mortgages(nullptr), mortgageCount(0), mortgageCapacity(0){
    color = Color::None;
}

Property::Property(const MyString& name, int price, int baseRent, Color color)
    : name(name), price(price), baseRent(baseRent), owner(nullptr), mortgages(nullptr), mortgageCount(0), mortgageCapacity(0), color(color){}

Property::Property(const Property& other) : name(other.name), price(other.price), baseRent(other.baseRent), owner(other.owner), mortgageCount(other.mortgageCount), mortgageCapacity(other.mortgageCapacity) {
    mortgages = new Mortgage * [mortgageCapacity];
    for (int i = 0; i < mortgageCount; ++i)
        mortgages[i] = other.mortgages[i]->clone();
    color = other.color;
}

Property& Property::operator=(const Property& other) {
    if (this != &other) {
        for (int i = 0; i < mortgageCount; ++i)
            delete mortgages[i];
        delete[] mortgages;

        name = other.name;
        price = other.price;
        baseRent = other.baseRent;
        owner = other.owner;
        mortgageCount = other.mortgageCount;
        mortgageCapacity = other.mortgageCapacity;
        color = other.color;

        mortgages = new Mortgage * [mortgageCapacity];
        for (int i = 0; i < mortgageCount; ++i)
            mortgages[i] = other.mortgages[i]->clone();
    }
    return *this;
}

Property::~Property() {
    for (int i = 0; i < mortgageCount; ++i)
        delete mortgages[i];
    delete[] mortgages;
}

void Property::onLand(Player& player) {
   
    if (!owner) {
        std::cout << player.getName() << " landed on " << name.c_str() << ". It costs $" << price << ". Buy it? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (player.getBalance() >= price) {
                player.pay(price);
                setOwner(&player);
                player.addOwnedProperty(this);
                std::cout << player.getName() << " bought " << name.c_str() << "!\n";
            }
            else {
                std::cout << "Not enough money to buy the property.\n";
            }
        }
    }
    else if (owner != &player) {
        int rent = calculateRent();
        std::cout << player.getName() << " landed on " << name.c_str() << " owned by " << owner->getName()
            << ". Pays rent: $" << rent << ".\n";

        if (player.getBalance() < rent) {
            std::cout << player.getName() << " payed rent and went bankrupt!\n";
        }
        player.pay(rent);
        owner->receive(rent);
    }
}

void Property::buildCottage() {
    if (mortgageCount >= mortgageCapacity)
        resizeMortgages();
    mortgages[mortgageCount++] = new Cottage();
}

void Property::buildCastle() {
    if (mortgageCount >= mortgageCapacity)
        resizeMortgages();
    mortgages[mortgageCount++] = new Castle();
}

int Property::calculateRent() const {
    int totalBonus = 0;
    for (int i = 0; i < mortgageCount; ++i)
        totalBonus += mortgages[i]->getRentBonus(baseRent);
    return baseRent + totalBonus;
}

Player* Property::getOwner() const { return owner; }
void Property::setOwner(Player* newOwner) { owner = newOwner; }

void Property::removeOwnership()
{
    owner = nullptr;
    for (size_t i = 0; i < mortgageCount; i++)
    {
        delete mortgages[i];
    }
    mortgageCount = 0;
}

const MyString& Property::getName() const { return name; }
int Property::getPrice() const { return price; }
int Property::getBaseRent() const { return baseRent; }

Color Property::getColor() const {
    return color;
}

Field* Property::clone() const
{
    return new Property();
}

