#include <gtest/gtest.h>
#include "Vector2d.h"

TEST(VectorTest, Add)
{
    LB3::Vector2d first(1,2);
    LB3::Vector2d second(3, 4);
    LB3::Vector2d result = first + second;
    ASSERT_EQ(result.x, 4);
    ASSERT_EQ(result.y, 6);
}

TEST(VectorTest, AddNegative)
{
    LB3::Vector2d first(0, -2);
    LB3::Vector2d second(-1, 4);
    LB3::Vector2d result = first + second;
    ASSERT_EQ(result.x, -1);
    ASSERT_EQ(result.y, 2);
}