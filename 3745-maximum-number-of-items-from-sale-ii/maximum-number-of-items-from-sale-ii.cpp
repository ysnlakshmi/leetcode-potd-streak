#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        long long min_price = 2e9;

        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, (long long)item[1]);
        }

        vector<int> mult_count(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            if (freq[f] == 0) continue;
            for (int m = f; m <= n; m += f) {
                mult_count[f] += freq[m];
            }
            mult_count[f] -= 1;
        }

        vector<pair<long long, long long>> bundles;
        bundles.reserve(n);
        for (const auto& item : items) {
            int f = item[0];
            long long p = item[1];
            if (mult_count[f] > 0) {
                bundles.push_back({p, mult_count[f]});
            }
        }

        sort(bundles.begin(), bundles.end());

        long long rem_budget = budget;
        long long bundle_copies = 0;
        long long max_copies = rem_budget / min_price;

        for (const auto& [price, count] : bundles) {
            if (rem_budget < price) break;

            long long take = min(count, rem_budget / price);
            rem_budget -= take * price;
            bundle_copies += 2 * take;

            max_copies = max(max_copies, bundle_copies + rem_budget / min_price);
        }

        return (int)max_copies;
    }
};