#include "Monopoly.h"
#include "Property.h"
#include "ColorUtils.h"
#include <iostream>

int main() {
    Monopoly game(2); // или 3, 4 и т.н.

    while (true) {
        game.playTurn();
        std::cout << "Press Enter to continue to next player...\n";
        std::cin.ignore(); // за да изчака Enter
        std::cin.get();    // действителното Enter
    }

    return 0;
}