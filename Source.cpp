#include "Monopoly.h"
#include "Property.h"
#include "ColorUtils.h"
#include <iostream>

int main() {
    Monopoly game(2); // ��� 3, 4 � �.�.

    while (true) {
        game.playTurn();
        std::cout << "Press Enter to continue to next player...\n";
        std::cin.ignore(); // �� �� ������ Enter
        std::cin.get();    // �������������� Enter
    }

    return 0;
}