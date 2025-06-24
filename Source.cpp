#include "Monopoly.h"
#include <ctime>    // �� srand
#include <cstdlib>  // �� rand
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // ������������ ���������� �� �������� �����

    std::cout << "Welcome to Monopoly!\n";

    int playerCount;
    do {
        std::cout << "Enter number of players (2-6): ";
        std::cin >> playerCount;
    } while (playerCount < 2 || playerCount > 6);

    Monopoly game(playerCount);
    game.startGame();  // ����� ������, ������ ������ 1 �����

    return 0;
}
