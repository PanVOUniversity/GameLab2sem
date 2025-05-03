#include <gtest/gtest.h>
#include "unit.h"
#include "field.h"
#include "hill.h"
#include "fortress.h"
#include "player.h"
#include <vector>

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
    EXPECT_EQ(unit->getHealth(), 10);
    EXPECT_EQ(unit->getDamage(), 5);
    EXPECT_TRUE(unit->getPlayer());
    EXPECT_EQ(unit->getWill(), 3);
}

TEST_F(UnitTest, SettersUpdateValuesCorrectly)
{
    unit->setAttackDistance(4);
    unit->setHealth(15);
    unit->setDamage(8);
    unit->setPlayer(false);
    unit->setWill(2);

    EXPECT_EQ(unit->getAttackDistance(), 4);
    EXPECT_EQ(unit->getHealth(), 15);
    EXPECT_EQ(unit->getDamage(), 8);
    EXPECT_FALSE(unit->getPlayer());
    EXPECT_EQ(unit->getWill(), 2);
}

// Test fixture for Field class
class FieldTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        field = new Field(3, 4);
        unit = new Unit("TestUnit", 1, 1, 10, 5);
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
        unit = new Unit("TestUnit", 1, 1, 10, 5);
        hill = new Hill(2, 3, 5, unit);
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
    EXPECT_EQ(hill->getHeight(), 5);
}

TEST_F(HillTest, HeightCanBeUpdated)
{
    hill->setHeight(7);
    EXPECT_EQ(hill->getHeight(), 7);
}

// Test fixture for Fortress class
class FortressTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        unit = new Unit("TestUnit", 1, 1, 10, 5);
        fortress = new Fortress(1, 1, 3, 10, unit);
    }

    void TearDown() override
    {
        delete fortress; // Will delete the unit as well
    }

    Fortress* fortress;
    Unit* unit;
};

TEST_F(FortressTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(fortress->getX(), 1);
    EXPECT_EQ(fortress->getY(), 1);
    EXPECT_EQ(fortress->getUnit(), unit);
    EXPECT_EQ(fortress->getHeight(), 3);
    EXPECT_EQ(fortress->getStrength(), 10);
}

TEST_F(FortressTest, StrengthManagementWorksCorrectly)
{
    fortress->setStrength(8);
    EXPECT_EQ(fortress->getStrength(), 8);

    // Test destruction condition
    EXPECT_FALSE(fortress->setStrength(5));
    EXPECT_TRUE(fortress->setStrength(0));
    EXPECT_TRUE(fortress->setStrength(-1));
}

// Test fixture for Player class
class PlayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        player = new Player("TestPlayer", true, false, false, 10);
        unit1 = new Unit("Unit1", 1, 1, 10, 5);
        unit2 = new Unit("Unit2", 2, 2, 15, 7);
    }

    void TearDown() override
    {
        delete player;
        delete unit1;
        delete unit2;
    }

    Player* player;
    Unit* unit1;
    Unit* unit2;
};

TEST_F(PlayerTest, ConstructorInitializesValuesCorrectly)
{
    EXPECT_EQ(player->getName(), "TestPlayer");
    EXPECT_TRUE(player->getMyTurn());
    EXPECT_FALSE(player->getAI());
    EXPECT_FALSE(player->getDefeated());
    EXPECT_EQ(player->getMana(), 10);
    EXPECT_TRUE(player->getMyUnits().empty());
}

TEST_F(PlayerTest, UnitManagementWorksCorrectly)
{
    std::vector<Unit*> units = {unit1, unit2};
    player->setMyUnits(units);

    auto playerUnits = player->getMyUnits();
    EXPECT_EQ(playerUnits.size(), 2);
    EXPECT_EQ(playerUnits[0]->getName(), "Unit1");
    EXPECT_EQ(playerUnits[1]->getName(), "Unit2");
}

TEST_F(PlayerTest, StateManagementWorksCorrectly)
{
    player->setMyTurn(false);
    player->setAI(true);
    player->setDefeated(true);
    player->setMana(5);

    EXPECT_FALSE(player->getMyTurn());
    EXPECT_TRUE(player->getAI());
    EXPECT_TRUE(player->getDefeated());
    EXPECT_EQ(player->getMana(), 5);
}

// Test for class hierarchies
TEST(ClassHierarchyTest, InheritanceRelationships)
{
    // Test Field -> Hill inheritance
    Hill* hill = new Hill(0, 0, 3);
    Field* field = hill;
    EXPECT_EQ(field->getX(), 0);
    EXPECT_EQ(field->getY(), 0);
    delete hill;

    // Test Hill -> Fortress inheritance
    Fortress* fortress = new Fortress(1, 1, 5, 10);
    Hill* hill2 = fortress;
    EXPECT_EQ(hill2->getX(), 1);
    EXPECT_EQ(hill2->getY(), 1);
    EXPECT_EQ(hill2->getHeight(), 5);
    delete fortress;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}