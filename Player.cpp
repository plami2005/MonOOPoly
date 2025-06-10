#include "Player.h"
#include <cstring>
#include <iostream>

Player::Player() : name("Unnamed"), balance(1500), position(0), inJail(false) {}

Player::Player(int playerId, const MyString& name, int balance) : name(name), balance(1500), position(0), inJail(false) {}

void Player::move(int steps) {
    if (!inJail)
        position = (position + steps) % 40; // 40 позиции по дъската
}

void Player::pay(int amount) {
    balance -= amount;
    if (balance < 0) balance = 0;
}

void Player::receive(int amount) {
    balance += amount;
}

void Player::goToJail() {
    inJail = true;
    jailTurns = 0;
    position = 10; // позиция за "Jail"
}

void Player::leaveJail() {
    inJail = false;
    jailTurns = 0;
}

bool Player::isBankrupt() const {
    return balance <= 0;
}

int Player::getPlayerId() const
{
    return playerId;
}

const MyString& Player::getName() const {
    return name;
}

int Player::getBalance() const {
    return balance;
}

int Player::getPosition() const {
    return position;
}

int Player::getPairsCount() const
{
    return pairsCount;
}

bool Player::isInJail() const {
    return inJail;
}

void Player::addProperty(Property* property) {
    properties.push_back(property);
}

void Player::removeProperty(Property* property)
{
    properties.erase(properties.find(property));
}

const MyVector<Property*>& Player::getProperties() const {
    return properties;
}

void Player::saveToBinary(std::ofstream& out) const {
    size_t len = name.getSize();
    out.write((char*)&len, sizeof(len));
    out.write(name.c_str(), len);

    out.write((char*)&balance, sizeof(balance));
    out.write((char*)&position, sizeof(position));
    out.write((char*)&inJail, sizeof(inJail));
    out.write((char*)&jailTurns, sizeof(jailTurns));
}

void Player::loadFromBinary(std::ifstream& in) {

    size_t len;
    in.read((char*)&len, sizeof(len));

    char* buff = new char[len + 1];
    in.read(buff, len);
    buff[len] = '\0';
    name = MyString(buff);
    delete[] buff;

    in.read((char*)&balance, sizeof(balance));
    in.read((char*)&position, sizeof(position));
    in.read((char*)&inJail, sizeof(inJail));
    in.read((char*)&jailTurns, sizeof(jailTurns));
}
