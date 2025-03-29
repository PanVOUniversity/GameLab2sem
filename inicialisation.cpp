// Updated inicialisation.cpp
#include "inicialisation.h"

#include "inicialisation.h"
#include <stdexcept> // for std::invalid_argument

std::vector<std::vector<Field*>> createBoard(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Board dimensions must be positive");
    }

    std::vector<std::vector<Field*>> board(
        static_cast<size_t>(width),
        std::vector<Field*>(static_cast<size_t>(height))
    );

    for (size_t x = 0; x < board.size(); ++x) {
        for (size_t y = 0; y < board[0].size(); ++y) {
            board[x][y] = new Field(static_cast<int>(x), static_cast<int>(y));
        }
    }

    return board;
}

void placeHills(std::vector<std::vector<Field*>>& board, int numHills) {
    if (numHills <= 0) return;
    if (board.empty() || board[0].empty()) return;

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < numHills; ++i) {
        size_t x = static_cast<size_t>(rand() % board.size());
        size_t y = static_cast<size_t>(rand() % board[0].size());
        
        // Delete existing field if it's not already a hill
        if (!dynamic_cast<Hill*>(board[x][y])) {
            delete board[x][y];
            board[x][y] = new Hill(
                static_cast<int>(x),
                static_cast<int>(y),
                2 // Assuming 2 is the default hill height
            );
        }
    }
}

GameData inicialisation(int width, int height, int numHills, const std::string& name1, const std::string& name2) {
    GameData gameData;
    
    // Create game board
    gameData.board = createBoard(width, height);
    
    // Place hills on the board
    placeHills(gameData.board, numHills);
    
    // Create players
    gameData.player1 = new Player(true, false, false, 100); // Human player
    gameData.player2 = new Player(false, true, false, 100); // AI player
    
    return gameData;
}
