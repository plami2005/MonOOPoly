#pragma once
#include "Field.h"

class GoToJailField : public Field {
public:
    void onLand(Player& player) override;
};
