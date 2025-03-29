#include "gtest/gtest.h"
#include "unit.h"
#include "field.h"
#include "functions.h"
#include "getcommands.h"
#include "player.h"
#include <vector>
#include <sstream>

// Test fixture for all tests
class GameTest : public ::testing::Test {
protected:
    std::vector<std::vector<Field*>> board;
    
    void SetUp() override {
        board = createTestBoard(10, 10);
    }
    
    void TearDown() override {
        cleanupTestBoard(board);
    }
    
    std::vector<std::vector<Field*>> createTestBoard(int width, int height) {
        std::vector<std::vector<Field*>> b(width, std::vector<Field*>(height));
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                b[x][y] = new Field(x, y);
            }
        }
        return b;
    }
    
    void cleanupTestBoard(std::vector<std::vector<Field*>>& b) {
        for (auto& row : b) {
            for (auto field : row) {
                delete field->getUnit(); // Clean up any units
                delete field;
            }
        }
    }
};

// Parameterized attack tests
struct AttackTestParams {
    std::string testName;
    int attackerWill;
    int attackerDamage;
    int attackerAttackDistance;
    int victimHealth;
    int victimDistance;
    bool expectedAttackSuccess;
    int expectedVictimHealth;
    int expectedAttackerWill;
    bool expectVictimDefeated;
};

class AttackTest : public GameTest, public ::testing::WithParamInterface<AttackTestParams> {};

TEST_P(AttackTest, VariousAttackScenarios) {
    const auto& params = GetParam();
    
    Unit* attacker = new Unit("Knight", 3, params.attackerAttackDistance, 
                             100, params.attackerDamage, false, params.attackerWill);
    Unit* victim = new Unit("Archer", 2, 3, params.victimHealth, 10, true, 2);
    
    board[0][0]->setUnit(attacker);
    board[0][params.victimDistance]->setUnit(victim);

    attack(board, 0, 0, 0, params.victimDistance);

    if (params.expectedAttackSuccess) {
        EXPECT_EQ(victim->getHealth(), params.expectedVictimHealth);
        EXPECT_EQ(attacker->getWill(), params.expectedAttackerWill);
        EXPECT_EQ(board[0][params.victimDistance]->getUnit() == nullptr, 
                 params.expectVictimDefeated);
    } else {
        EXPECT_EQ(victim->getHealth(), params.victimHealth);
        EXPECT_EQ(attacker->getWill(), params.attackerWill);
    }
}

INSTANTIATE_TEST_SUITE_P(
    AttackScenarios,
    AttackTest,
    ::testing::Values(
        AttackTestParams{"SuccessfulAttack", 3, 20, 2, 50, 1, true, 30, 2, false},
        AttackTestParams{"InsufficientWill", 0, 20, 2, 50, 1, false, 50, 0, false},
        AttackTestParams{"OutOfRangeAttack", 3, 20, 2, 50, 4, false, 50, 3, false},
        AttackTestParams{"VictimDefeated", 3, 60, 2, 50, 1, true, -10, 2, true}
    )
);

// Command tests
class CommandTest : public GameTest {
protected:
    void mockCommands(Player* player, const std::string& input) {
        std::istringstream testInput(input);
        std::streambuf* origCin = std::cin.rdbuf(testInput.rdbuf());
        getPlayerCommands(player, board);
        std::cin.rdbuf(origCin);
    }
};

TEST_F(CommandTest, HumanPlayerCanMove) {
    Unit* unit = new Unit("Knight", 2, 1, 10, 5);
    board[1][1]->setUnit(unit);
    Player humanPlayer(true, false);
    
    testing::internal::CaptureStdout();
    mockCommands(&humanPlayer, "move 1 1 2 2\nn\n");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(board[1][1]->getUnit(), nullptr);
    EXPECT_EQ(board[2][2]->getUnit(), unit);
    EXPECT_EQ(unit->getWill(), 1);
    EXPECT_NE(output.find("Knight moved"), std::string::npos);
}

TEST_F(CommandTest, AIPlayerBlocked) {
    Player aiPlayer(true, true);
    
    testing::internal::CaptureStdout();
    mockCommands(&aiPlayer, "move 0 0 0 1\nn\n");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("AI player's turn"), std::string::npos);
}

TEST_F(CommandTest, InvalidCommandsHandled) {
    Player humanPlayer(true, false);
    
    testing::internal::CaptureStdout();
    mockCommands(&humanPlayer, "invalid\nmove bad args\nn\n");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Unknown command"), std::string::npos);
    EXPECT_NE(output.find("Invalid move command"), std::string::npos);
}