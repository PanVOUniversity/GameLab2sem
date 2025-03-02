#include <gtest/gtest.h>
#include "inicialisation.h"
#include "player.h"
#include "unit.h"
#include "hill.h"
#include "field.h"

TEST(BoardTest, CreateBoardTest) {
    auto board = createBoard(10, 10);
    EXPECT_EQ(board.size(), 10);
    EXPECT_EQ(board[0].size(), 10);
    
    // Cleanup
    for (auto& row : board) {
        for (auto field : row) {
            delete field;
        }
    }
}

TEST(HillTest, PlaceHillsTest) {
    auto board = createBoard(10, 10);
    placeHills(board);
    
    int hillCount = 0;
    for (const auto& row : board) {
        for (const auto field : row) {
            if (dynamic_cast<Hill*>(field)) hillCount++;
        }
    }
    EXPECT_EQ(hillCount, 10);
    
    // Cleanup
    for (auto& row : board) {
        for (auto field : row) {
            delete field;
        }
    }
}

TEST(PlayerTest, CreatePlayersTest) {
    Player user(1, 0, 0, 40);
    Player ai(0, 1, 0, 40);
    
    EXPECT_EQ(user.getMyTurn(), true);
    EXPECT_EQ(user.getAI(), false);
    EXPECT_EQ(user.getMana(), 40);
    
    EXPECT_EQ(ai.getMyTurn(), false);
    EXPECT_EQ(ai.getAI(), true);
    EXPECT_EQ(ai.getMana(), 40);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}