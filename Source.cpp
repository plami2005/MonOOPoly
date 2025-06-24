#include "Monopoly.h"
#include <ctime>  
#include <iostream>

int main() {
    std::srand((unsigned)std::time(nullptr));

    std::cout << "Welcome to Monopoly!\n";

    int playerCount;
    do {
        std::cout << "Enter number of players (2-6): ";
        std::cin >> playerCount;
    } while (playerCount < 2 || playerCount > 6);

    Monopoly game(playerCount);
    game.startGame(); 

    return 0;
}
