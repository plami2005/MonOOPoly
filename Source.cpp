#include "Monopoly.h"
#include <ctime>    // за srand
#include <cstdlib>  // за rand
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Инициализира генератора на случайни числа

    std::cout << "Welcome to Monopoly!\n";

    int playerCount;
    do {
        std::cout << "Enter number of players (2-6): ";
        std::cin >> playerCount;
    } while (playerCount < 2 || playerCount > 6);

    Monopoly game(playerCount);
    game.startGame();  // Върти ходове, докато остане 1 играч

    return 0;
}
