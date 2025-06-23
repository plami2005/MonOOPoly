#pragma once
#include "Player.h"
#include "Board.h"
#include "Bank.h"
#include "CardDeck.h"
#include "CardField.h"
#include "GoToJailField.h"

class Monopoly {
    Player** players;
    int playerCount;
    int currentPlayerIndex;
    Board* board;
    Bank bank;
    CardDeck cardDeck;

public:
    Monopoly(int playerCount);
    ~Monopoly();

    void startGame();
    void playTurn();
    bool isGameOver() const;
    void printGameState() const;
    Board* getBoard() const;
};
