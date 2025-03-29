#include "gtest/gtest.h"
#include "unit.h"
#include "field.h"
#include "functions.h"
#include <vector>

// Helper function to create a test board
std::vector<std::vector<Field*>> createTestBoard(int width, int height)
{
    std::vector<std::vector<Field*>> board(width, std::vector<Field*>(height));

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            board[x][y] = new Field(x, y);
        }
    }

    return board;
}

// Helper function to clean up the test board
void cleanupTestBoard(std::vector<std::vector<Field*>>& board)
{
    for (auto& row : board)
    {
        for (auto field : row)
        {
            delete field;
        }
    }
}

// Test fixture for attack function
struct AttackTestParams
{
    std::string testName;               // Name of the test scenario
    int attackerWill;                   // Attacker's initial Will
    int attackerDamage;                 // Attacker's damage
    int attackerAttackDistance;         // Attacker's attack range
    int victimHealth;                   // Victim's initial health
    int victimDistance;                 // Distance between attacker and victim
    bool expectedAttackSuccess;         // Whether the attack should succeed
    int expectedVictimHealth;           // Expected victim health after attack
    int expectedAttackerWill;           // Expected attacker Will after attack
    bool expectVictimDefeated;          // Whether the victim should be defeated
};

// Parameterized test case
class AttackTest : public ::testing::TestWithParam<AttackTestParams> {};

TEST_P(AttackTest, AttackScenarios)
{
    // Get test parameters
    const AttackTestParams& params = GetParam();

    // Create a 10x10 board
    auto board = createTestBoard(10, 10);

    // Create attacker and victim units
    Unit* attacker = new Unit(
        "Knight",
        3,                          // move_distance
        params.attackerAttackDistance, // attack_distance
        100,                        // health
        params.attackerDamage,
        false,
        params.attackerWill
    );

    Unit* victim = new Unit(
        "Archer",
        2,                          // move_distance
        3,                          // attack_distance
        params.victimHealth,        // health
        10,                         // damage
        true,                       // player
        2                           // will
    );

    // Place units on the board
    board[0][0]->setUnit(attacker);
    board[0][params.victimDistance]->setUnit(victim);

    // Perform attack
    attack(board, 0, 0, 0, params.victimDistance);

    // Check results
    if (params.expectedAttackSuccess)
    {
        EXPECT_EQ(victim->getHealth(), params.expectedVictimHealth);
        EXPECT_EQ(attacker->getWill(), params.expectedAttackerWill);

        if (params.expectVictimDefeated)
        {
            EXPECT_EQ(board[0][params.victimDistance]->getUnit(), nullptr); // Victim removed
        }
        else
        {
            EXPECT_NE(board[0][params.victimDistance]->getUnit(), nullptr); // Victim still alive
        }
    }
    else
    {
        EXPECT_EQ(victim->getHealth(), params.victimHealth); // No damage
        EXPECT_EQ(attacker->getWill(), params.attackerWill); // Will unchanged
    }

    // Clean up
    cleanupTestBoard(board);
}

// Define test scenarios
INSTANTIATE_TEST_SUITE_P(
    AttackScenarios,
    AttackTest,
    ::testing::Values(
        // Successful attack
        AttackTestParams
{
    "SuccessfulAttack",
    3,   // Attacker Will
    20,  // Attacker Damage
    2,   // Attacker Attack Distance
    50,  // Victim Health
    1,   // Victim Distance (within range)
    true, // Attack succeeds
    30,  // Expected victim health (50 - 20)
    2,   // Expected attacker Will (3 - 1)
    false // Victim not defeated
},
// Insufficient Will
AttackTestParams
{
    "InsufficientWill",
    0,   // Attacker Will
    20,  // Attacker Damage
    2,   // Attacker Attack Distance
    50,  // Victim Health
    1,   // Victim Distance
    false, // Attack fails
    50,  // Expected victim health (unchanged)
    0,   // Expected attacker Will (unchanged)
    false
},
// Out of range attack
AttackTestParams
{
    "OutOfRangeAttack",
    3,   // Attacker Will
    20,  // Attacker Damage
    2,   // Attacker Attack Distance (range = 2)
    50,  // Victim Health
    4,   // Victim Distance (out of range)
    false, // Attack fails
    50,  // Expected victim health (unchanged)
    3,   // Expected attacker Will (unchanged)
    false
},
// Victim defeated
AttackTestParams
{
    "VictimDefeated",
    3,   // Attacker Will
    60,  // Attacker Damage (high)
    2,   // Attacker Attack Distance
    50,  // Victim Health
    1,   // Victim Distance
    true, // Attack succeeds
    -10, // Expected victim health (50 - 60)
    2,   // Expected attacker Will (3 - 1)
    true // Victim defeated
}
    )
);