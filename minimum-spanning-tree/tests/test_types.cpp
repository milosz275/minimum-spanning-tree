#include <gtest/gtest.h>
#include "common/types.h"

TEST(EuclideanTest, Basic)
{
    Point a{ 0, 0 }, b{ 3, 4 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 5.0);
}

TEST(EuclideanTest, SamePoint)
{
    Point a{ 1, 1 }, b{ 1, 1 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 0.0);
}

TEST(EuclideanTest, NegativeCoordinates)
{
    Point a{ -1, -2 }, b{ -4, -6 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 5.0);
}

TEST(EuclideanTest, MixedCoordinates)
{
    Point a{ -3, 4 }, b{ 3, -4 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 10.0);
}

TEST(EuclideanTest, HorizontalDistance)
{
    Point a{ 2, 5 }, b{ 7, 5 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 5.0);
}

TEST(EuclideanTest, VerticalDistance)
{
    Point a{ 3, 8 }, b{ 3, 2 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 6.0);
}

TEST(EuclideanTest, LargeCoordinates)
{
    Point a{ 10000, 20000 }, b{ 30000, 40000 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 28284.2712474619);
}

TEST(EuclideanTest, ZeroCoordinates)
{
    Point a{ 0, 0 }, b{ 0, 0 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 0.0);
}

TEST(EuclideanTest, DiagonalDistance)
{
    Point a{ 1, 1 }, b{ 4, 5 };
    EXPECT_DOUBLE_EQ(euclidean(a, b), 5.0);
}
