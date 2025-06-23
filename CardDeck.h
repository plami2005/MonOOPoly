#pragma once
#include "Card.h"

class CardDeck {
    Card** cards;
    int size;
    int capacity;
    int drawIndex;

public:
    CardDeck();
    CardDeck(const CardDeck& other);
    CardDeck& operator=(const CardDeck& other);
    ~CardDeck();

    void addCard(Card* card);
    Card* drawCard();
    void returnCardToBottom(Card* card);
};