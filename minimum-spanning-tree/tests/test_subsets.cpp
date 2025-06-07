#include <gtest/gtest.h>
#include "model/subsets.h"

// Subsets of size < 3 should be excluded. Full set is allowed.
TEST(SubsetGenerationTest, NoTrivialSubsetsOnly)
{
    int n = 5;
    auto subsets = generateSubsets(n);

    for (const auto& subset : subsets)
        EXPECT_GE(subset.size(), 3);   // No size 0, 1, 2
}

// For n = 4, size-3 and full set
TEST(SubsetGenerationTest, CountCorrectForN4)
{
    int n = 4;
    auto subsets = generateSubsets(n);
    EXPECT_EQ(subsets.size(), 5);  // 4 size-3 subsets + 1 full set
}

TEST(SubsetGenerationTest, ManualPrintN3)
{
    auto subsets = generateSubsets(3);
    for (const auto& s : subsets)
    {
        std::cout << "{ ";
        for (int v : s) std::cout << v << " ";
        std::cout << "}\n";
    }
    EXPECT_FALSE(subsets.empty());
}

// For n = 3, only one valid subset: {0,1,2}
TEST(SubsetGenerationTest, CorrectSubsetsForN3)
{
    int n = 3;
    auto subsets = generateSubsets(n);

    std::set<std::set<int>> expected = {
        {0, 1, 2}
    };

    std::set<std::set<int>> actual;
    for (const auto& s : subsets)
        actual.insert(std::set<int>(s.begin(), s.end()));

    EXPECT_EQ(actual, expected);
}

// For n = 0 or n = 1, no valid subsets
TEST(SubsetGenerationTest, EmptyWhenNIsZeroOrOne)
{
    EXPECT_TRUE(generateSubsets(0).empty());
    EXPECT_TRUE(generateSubsets(1).empty());
}

// For n = 2, no subsets meet min size requirement of 3
TEST(SubsetGenerationTest, EmptyWhenNTwo)
{
    EXPECT_TRUE(generateSubsets(2).empty());
}

// Subsets must be unique
TEST(SubsetGenerationTest, NoDuplicateSubsets)
{
    int n = 5;
    auto subsets = generateSubsets(n);
    std::set<std::set<int>> unique;
    for (const auto& s : subsets)
        unique.insert(std::set<int>(s.begin(), s.end()));
    EXPECT_EQ(unique.size(), subsets.size());
}
