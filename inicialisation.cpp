// Updated inicialisation.cpp
#include "inicialisation.h"
#include "hill.h"
#include <cstdlib>
#include <ctime>
#include "player.h"
#include <cstddef>

std::vector<std::vector<Field*>> createBoard(int width, int height) {
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

void placeHills(std::vector<std::vector<Field*>>& board) {
    srand(time(0));
    for (int i = 0; i < 10; ++i) {
        size_t x = static_cast<size_t>(rand() % board.size());
        size_t y = static_cast<size_t>(rand() % board[0].size());
        delete board[x][y];
        board[x][y] = new Hill(
            static_cast<int>(x), 
            static_cast<int>(y), 
            2
        );
    }
}