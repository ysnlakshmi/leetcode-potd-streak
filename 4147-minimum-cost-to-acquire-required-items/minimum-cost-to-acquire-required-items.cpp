#include <algorithm>

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long minCost = -1;

        auto calculateCost = [&](long long i) {
            long long currentCost = i * costBoth;
            long long rem1 = std::max(0LL, (long long)need1 - i);
            long long rem2 = std::max(0LL, (long long)need2 - i);
            currentCost += rem1 * cost1 + rem2 * cost2;
            return currentCost;
        };

        long long candidates[] = {
            0,
            need1,
            need2,
            std::max((long long)need1, (long long)need2)
        };

        for (long long i : candidates) {
            long long cost = calculateCost(i);
            if (minCost == -1 || cost < minCost) {
                minCost = cost;
            }
        }

        long long maxNeed = std::max((long long)need1, (long long)need2);
        long long costBeyond = calculateCost(maxNeed + 1);
        if (minCost == -1 || costBeyond < minCost) {
            minCost = costBeyond;
        }

        return minCost;
    }
};