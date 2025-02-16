#include <gtest/gtest.h>
#include "main.h"

TEST(True_test, ReturnsTrue)
{
    EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}