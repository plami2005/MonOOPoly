#pragma once
#include "Field.h"

class GoToJailField : public Field {
public:
    void onLand(Player& player) override;
    virtual Field* clone() const override;
};
