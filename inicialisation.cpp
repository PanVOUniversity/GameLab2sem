#include "inicialisation.h"
#include "hill.h"
#include <cstdlib>
#include <ctime>
#include "player.h"

std::vector<std::vector<Field*>> createBoard(int width, int height) {
    std::vector<std::vector<Field*>> board(width, std::vector<Field*>(height));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            board[x][y] = new Field(x, y);
        }
    }
    return board;
}

void placeHills(std::vector<std::vector<Field*>>& board) {
    srand(time(0));
    for (int i = 0; i < 10; ++i) {
        int x = rand() % 10;
        int y = rand() % 10;
        delete board[x][y];
        board[x][y] = new Hill(x, y, 2);
    }
}

void createPlayers() {
    Player user(true, false, false, 40);
    Player ai(false, true, false, 40);
}

void inicialisation() {
    auto board = createBoard(10, 10);
    placeHills(board);
    createPlayers();
    
    // Cleanup board
    for (auto& row : board) {
        for (auto field : row) {
            delete field;
        }
    }
}