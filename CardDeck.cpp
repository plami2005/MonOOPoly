#include "CardDeck.h"
#include <cstdlib>
#include <ctime>

CardDeck::CardDeck() : cards(nullptr), size(0), capacity(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

CardDeck::CardDeck(const CardDeck& other) : size(other.size), capacity(other.capacity) {
    cards = new Card * [capacity];
    for (int i = 0; i < size; ++i)
        cards[i] = other.cards[i]->clone();
}

CardDeck& CardDeck::operator=(const CardDeck& other) {
    if (this != &other) {
        for (int i = 0; i < size; ++i)
            delete cards[i];
        delete[] cards;

        size = other.size;
        capacity = other.capacity;
        cards = new Card * [capacity];
        for (int i = 0; i < size; ++i)
            cards[i] = other.cards[i]->clone();
    }
    return *this;
}

CardDeck::~CardDeck() {
    for (int i = 0; i < size; ++i)
        delete cards[i];
    delete[] cards;
}

void CardDeck::addCard(Card* card) {
    if (size >= capacity) {
        int newCap = capacity * 2;
        if (newCap == 0) newCap = 4;
        Card** newArr = new Card * [newCap];
        for (int i = 0; i < size; ++i)
            newArr[i] = cards[i];
        delete[] cards;
        cards = newArr;
        capacity = newCap;
    }
    cards[size++] = card;
}

Card* CardDeck::drawCard() {
    if (size == 0) return nullptr;
    int index = rand() % size;
    return cards[index];
}
