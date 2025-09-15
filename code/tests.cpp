#include <gtest/gtest.h>
#include "unit.h"
#include "field.h"
#include "hill.h"
#include "fortress.h"
#include "player.h"
#include <vector>
#include "getcommands.h"
#include "AI.h"
#include "functions.h"
#include "inicialisation.h"

// Test fixture for Unit class
class UnitTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        unit = new Unit("TestUnit", 2, 3, 10, 5, true, 3);
    }

    void TearDown() override
    {
        delete unit;
    }

    Unit* unit;
};

TEST_F(UnitTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(unit->getName(), "TestUnit");
    EXPECT_EQ(unit->getMoveDistance(), 2);
    EXPECT_EQ(unit->getAttackDistance(), 3);
    EXPECT_EQ(unit->getCurrentHealth(), 10);
    EXPECT_EQ(unit->getDamage(), 5);
    EXPECT_TRUE(unit->getPlayer());
    EXPECT_EQ(unit->getWill(), 3);
}

TEST_F(UnitTest, SettersUpdateValuesCorrectly)
{
    unit->setCurrentHealth(15);
    unit->setWill(2);
    EXPECT_EQ(unit->getCurrentHealth(), 15);
    EXPECT_EQ(unit->getWill(), 2);
}

// Test fixture for Field class
class FieldTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        field = new Field(3, 4);
        unit = new Unit("TestUnit", 1, 1, 10, 5, true, 2);
    }

    void TearDown() override
    {
        delete field;
        delete unit;
    }

    Field* field;
    Unit* unit;
};

TEST_F(FieldTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(field->getX(), 3);
    EXPECT_EQ(field->getY(), 4);
    EXPECT_EQ(field->getUnit(), nullptr);
}

TEST_F(FieldTest, UnitManagementWorksCorrectly)
{
    field->setUnit(unit);
    EXPECT_EQ(field->getUnit(), unit);

    field->setUnit(nullptr);
    EXPECT_EQ(field->getUnit(), nullptr);
}

// Test fixture for Hill class
class HillTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        unit = new Unit("TestUnit", 1, 1, 10, 5, true, 2);
        hill = new Hill(2, 3, unit);
    }

    void TearDown() override
    {
        delete hill; // Will delete the unit as well
    }

    Hill* hill;
    Unit* unit;
};

TEST_F(HillTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(hill->getX(), 2);
    EXPECT_EQ(hill->getY(), 3);
    EXPECT_EQ(hill->getUnit(), unit);
}

// Test fixture for Fortress class
class FortressTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        fortress = new Fortress(1, 1, 3, 10);
    }

    void TearDown() override
    {
        delete fortress;
    }

    Fortress* fortress;
};

TEST_F(FortressTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(fortress->getX(), 1);
    EXPECT_EQ(fortress->getY(), 1);
    EXPECT_EQ(fortress->getStrength(), 3);
    EXPECT_EQ(fortress->getMaxStrength(), 10);
}

TEST_F(FortressTest, StrengthManagementWorksCorrectly)
{
    fortress->setStrength(8);
    EXPECT_EQ(fortress->getStrength(), 8);
    fortress->setStrength(0);
    EXPECT_EQ(fortress->getStrength(), 0);
}

// Test fixture for Player class
class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        player = new Player("TestPlayer", true, false, false, 10);
    }

    void TearDown() override
    {
        delete player;
    }

    Player* player;
};

TEST_F(PlayerTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(player->getName(), "TestPlayer");
    EXPECT_TRUE(player->getMyTurn());
    EXPECT_FALSE(player->getAI());
    EXPECT_FALSE(player->getDefeated());
    EXPECT_EQ(player->getMana(), 10);
}

TEST_F(PlayerTest, StateManagementWorksCorrectly)
{
    player->setMyTurn(false);
    player->setDefeated(true);
    player->setMana(5);
    player->setSkippedTurns(2);
    EXPECT_FALSE(player->getMyTurn());
    EXPECT_TRUE(player->getDefeated());
    EXPECT_EQ(player->getMana(), 5);
    EXPECT_EQ(player->getSkippedTurns(), 2);
}

// Test for class hierarchies
TEST(ClassHierarchyTest, InheritanceRelationships)
{
    Hill* hill = new Hill(0, 0);
    Field* field = hill;
    EXPECT_EQ(field->getX(), 0);
    EXPECT_EQ(field->getY(), 0);
    delete hill;

    Fortress* fortress = new Fortress(1, 1, 5, 10);
    Field* field2 = fortress;
    EXPECT_EQ(field2->getX(), 1);
    EXPECT_EQ(field2->getY(), 1);
    delete fortress;
}

// --- Google Test stubs for uncovered functions ---

// getPlayerCommands is interactive; skip direct test or mock input if needed
// TEST(GetCommandsTest, GetPlayerCommands_Skipped) {}

TEST(GetCommandsTest, GetAICommands_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    EXPECT_NO_THROW(getAICommands(gameData.player2, gameData.board));
}

TEST(GetCommandsTest, MapAndDisplayFunctions_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    EXPECT_NO_THROW(unit_map(gameData.board));
    EXPECT_NO_THROW(field_map(gameData.board));
    EXPECT_NO_THROW(displayBoard(gameData.board));
}

// AI.cpp
TEST(AITest, AIact_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    EXPECT_NO_THROW(AIact(gameData.player2, gameData.board));
}

TEST(AITest, TryAIAttack_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 10, 5, false, 2);
    gameData.board[0][0]->setUnit(u);
    EXPECT_NO_THROW(tryAIAttack(u, 0, 0, gameData.board));
}

TEST(AITest, TryAIMove_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 10, 5, false, 2);
    gameData.board[0][0]->setUnit(u);
    EXPECT_NO_THROW(tryAIMove(u, 0, 0, gameData.board));
}

// functions.cpp
TEST(FunctionsTest, UpdateFortressStrength_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Fortress* f = new Fortress(1, 1, 2, 10);
    delete gameData.board[1][1];
    gameData.board[1][1] = f;
    EXPECT_NO_THROW(updateFortressStrength(gameData.board, 1, 1, 5));
}

TEST(FunctionsTest, CheckBombExplosions_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    EXPECT_NO_THROW(checkBombExplosions(gameData.board));
}

TEST(FunctionsTest, ApplyDamage_RemovesUnitOnZeroHealth) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 1, 1, true, 1);
    gameData.board[0][0]->setUnit(u);
    applyDamage(gameData.board, 0, 0, 2, nullptr);
    EXPECT_EQ(gameData.board[0][0]->getUnit(), nullptr);
}

TEST(FunctionsTest, Attack_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* attacker = new Unit("A", 1, 1, 10, 5, true, 2);
    Unit* target = new Unit("B", 1, 1, 10, 5, false, 2);
    gameData.board[0][0]->setUnit(attacker);
    gameData.board[0][1]->setUnit(target);
    EXPECT_NO_THROW(attack(gameData.board, 0, 0, 0, 1));
}

TEST(FunctionsTest, Move_UnitMoves) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 10, 5, true, 2);
    gameData.board[0][0]->setUnit(u);
    move(gameData.board, 0, 0, 1, 0);
    EXPECT_EQ(gameData.board[1][0]->getUnit(), u);
    EXPECT_EQ(gameData.board[0][0]->getUnit(), nullptr);
}

TEST(FunctionsTest, CreateShieldedField_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 10, 5, true, 2);
    createShieldedField(gameData.board, 0, 0, u);
    EXPECT_TRUE(dynamic_cast<ShieldedField*>(gameData.board[0][0]) != nullptr);
}

TEST(FunctionsTest, CreateHospitalField_NoCrash) {
    auto gameData = inicialisation(5, 5, 0, "P1", "P2", 10, true);
    Unit* u = new Unit("Test", 1, 1, 10, 5, true, 2);
    createHospitalField(gameData.board, 0, 0, u);
    EXPECT_TRUE(dynamic_cast<HospitalField*>(gameData.board[0][0]) != nullptr);
}

TEST(FunctionsTest, DisplayRules_NoCrash) {
    EXPECT_NO_THROW(displayRules());
}

// inicialisation.cpp
TEST(InitTest, Inicialisation_CreatesPlayersAndBoard) {
    auto gameData = inicialisation(5, 5, 2, "P1", "P2", 10, true);
    EXPECT_EQ(gameData.board.size(), 5u);
    EXPECT_EQ(gameData.player1->getName(), "P1");
    EXPECT_EQ(gameData.player2->getName(), "P2");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}