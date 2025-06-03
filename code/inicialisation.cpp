#include "inicialisation.h"
#include <stdexcept>
#include <cstdlib> // Required for rand(), srand()
#include <ctime>   // Required for time()
#include<iostream>

std::vector<std::vector<Field*>> createBoard(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Board dimensions must be positive");
    }

    std::vector<std::vector<Field*>> board(
                                      static_cast<size_t>(width),
                                      std::vector<Field*>(static_cast<size_t>(height))
                                  );

    for (size_t x = 0; x < board.size(); ++x)
    {
        for (size_t y = 0; y < board[0].size(); ++y)
        {
            board[x][y] = new Field(static_cast<int>(x), static_cast<int>(y));
        }
    }
    return board;
}

void placeHills(std::vector<std::vector<Field*>>& board, int numHills)
{
    if (numHills <= 0) return;
    if (board.empty() || board[0].empty()) return;

    // Seed the random number generator if not already seeded
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(0)));
        seeded = true;
    }


    int hillsPlaced = 0;
    int attempts = 0;
    int maxAttempts = numHills * 10; // Prevent infinite loops on small boards

    while (hillsPlaced < numHills && attempts < maxAttempts)
    {
        size_t x = static_cast<size_t>(rand() % board.size());
        size_t y = static_cast<size_t>(rand() % board[0].size());

        // Check if the field is currently a plain field before replacing it
        // This prevents replacing existing special fields or units
        if (board[x][y]->getType() == "plain" && board[x][y]->getUnit() == nullptr)
        {
            delete board[x][y];
            // Corrected: Pass nullptr as the third argument to the Hill constructor
            board[x][y] = new Hill(static_cast<int>(x), static_cast<int>(y), nullptr);
            hillsPlaced++;
        }
        attempts++;
    }

    if (hillsPlaced < numHills) {
        std::cerr << "Warning: Could only place " << hillsPlaced << " out of " << numHills << " hills after " << maxAttempts << " attempts.\n";
    }
}

GameData inicialisation(int width, int height, int numHills,
                        const std::string& name1, const std::string& name2,
                        int initialMana, bool player1Starts)
{
    GameData gameData;

    // Create game board
    gameData.board = createBoard(width, height);

    // Place hills on the board
    placeHills(gameData.board, numHills);

    // Create players with specified mana and turn order
    // The Player constructor now takes initialMana as the last parameter
    gameData.player1 = new Player(name1, player1Starts, false, false, initialMana);
    gameData.player2 = new Player(name2, !player1Starts, true, false, initialMana);

    return gameData;
}
