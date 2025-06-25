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

    void free();
    void copyFrom(const Monopoly& other);
    void moveFrom(Monopoly&& other);

public:
    Monopoly(int playerCount);
    Monopoly(const Monopoly& other);
    Monopoly(Monopoly&& other) noexcept;
    Monopoly& operator=(const Monopoly& other);
    Monopoly& operator=(Monopoly&& other) noexcept;
    ~Monopoly();

    Player* getWinner() const;
    void startGame();
    bool playTurn(); 
    bool isGameOver() const;
    void printGameState() const;
    Board* getBoard() const;
    void printCardDeck() const;
};
