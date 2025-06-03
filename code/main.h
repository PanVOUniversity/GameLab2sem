// main.h
#ifndef MAIN_H // Added include guard
#define MAIN_H

#include "inicialisation.h"
#include <iostream>
#include "getcommands.h"
#include "functions.h"
#include "AI.h" // Correct: Include the header file for declarations
#include "player.h" // Include Player header for checkVictory

// Forward declaration for checkVictory as used in main.cpp
void checkVictory(Player* player1, Player* player2, const std::vector<std::vector<Field*>>& board);


int main(); // Added forward declaration for main if needed, or keep as is if main.cpp includes main.h

#endif // MAIN_H
