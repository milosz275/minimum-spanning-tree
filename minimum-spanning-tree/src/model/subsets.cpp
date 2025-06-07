#include "model/subsets.h"

std::vector<std::vector<int>> generateSubsets(int n)
{
    std::vector<std::vector<int>> subsets;
    int max_mask = (1 << n); // 2^n

    for (int mask = 1; mask < max_mask; ++mask) // skip empty set only
    {
        std::vector<int> subset;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                subset.push_back(i);

        if (subset.size() >= 3) // or 2
            subsets.push_back(subset);
    }
    return subsets;
}
