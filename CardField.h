#pragma once
#include "Field.h"

class CardDeck;

class CardField : public Field {
    CardDeck* deck;

public:
    CardField() = default;
    CardField(CardDeck* deck);

    void onLand(Player& player) override;
    virtual Field* clone() const override;
};
