#pragma once
#include "Field.h"

class CardDeck;

class CardField : public Field {
    CardDeck* deck;

public:
    CardField(CardDeck* deck);

    void onLand(Player& player) override;
};
