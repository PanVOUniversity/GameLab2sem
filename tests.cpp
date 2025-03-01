#include <gtest/gtest.h>
#include "unit.h"
#include "player.h"
#include "field.h"

// Unit class tests
TEST(UnitTest, ConstructorInitialization) {
    Unit unit(2, 3, 100, 10, false); // player = false (enemy)

    EXPECT_EQ(unit.getMoveDistance(), 2);
    EXPECT_EQ(unit.getAttackDistance(), 3);
    EXPECT_EQ(unit.getHealth(), 100);
    EXPECT_EQ(unit.getDamage(), 10);
    EXPECT_EQ(unit.getPlayer(), false); // player is false (enemy)
}

TEST(UnitTest, SettersAndGetters) {
    Unit unit(1, 1, 50, 5, true); // player = true (user)

    unit.setAttackDistance(4);
    unit.setHealth(75);
    unit.setDamage(8);
    unit.setPlayer(false); // Change to enemy

    EXPECT_EQ(unit.getAttackDistance(), 4);
    EXPECT_EQ(unit.getHealth(), 75);
    EXPECT_EQ(unit.getDamage(), 8);
    EXPECT_EQ(unit.getPlayer(), false); // Now enemy
}

TEST(UnitTest, PlayerAssociation) {
    Unit unit(1, 1, 50, 5, true); // player = true (user)

    EXPECT_EQ(unit.getPlayer(), true); // User
    unit.setPlayer(false); // Change to enemy
    EXPECT_EQ(unit.getPlayer(), false); // Enemy
}

TEST(UnitTest, NameGetter) {
    Unit unit(1, 1, 50, 5, true);
    EXPECT_EQ(unit.getName(), ""); // Name is not set, should return empty string
}

// Field class tests
TEST(FieldTest, CoordinateInitialization) {
    Field field(5, 10);

    EXPECT_EQ(field.getX(), 5);
    EXPECT_EQ(field.getY(), 10);
    EXPECT_EQ(field.getUnit(), nullptr); // No unit assigned
}

TEST(FieldTest, UnitPlacement) {
    Unit unit(1, 1, 50, 5, true); // Create a unit
    Field field(0, 0, &unit); // Place the unit on the field

    EXPECT_EQ(field.getUnit(), &unit); // Check if the unit is correctly placed
    EXPECT_EQ(field.getX(), 0);
    EXPECT_EQ(field.getY(), 0);
}

TEST(FieldTest, UnitRemoval) {
    Unit unit(1, 1, 50, 5, true); // Create a unit
    Field field(0, 0, &unit); // Place the unit on the field

    EXPECT_EQ(field.getUnit(), &unit); // Unit is placed

    Field emptyField(1, 1); // Create a field without a unit
    EXPECT_EQ(emptyField.getUnit(), nullptr); // No unit assigned
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
