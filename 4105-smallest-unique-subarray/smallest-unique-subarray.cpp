#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const long long BASE1 = 1315423911LL;
        const long long MOD1 = 1000000007LL;
        const long long BASE2 = 2654435761LL;
        const long long MOD2 = 1000000009LL;

        vector<long long> p1(n + 1, 1), p2(n + 1, 1);
        vector<long long> h1(n + 1, 0), h2(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            long long val = static_cast<long long>(nums[i]) + 1;
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
            h1[i + 1] = (h1[i] * BASE1 + val) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + val) % MOD2;
        }

        auto getHash = [&](int l, int r) -> unsigned long long {
            long long x1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % MOD1;
            if (x1 < 0) x1 += MOD1;
            long long x2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % MOD2;
            if (x2 < 0) x2 += MOD2;
            return (static_cast<unsigned long long>(x1) << 32) | static_cast<unsigned long long>(x2);
        };

        auto hasUniqueOfLen = [&](int len) -> bool {
            unordered_map<unsigned long long, int> freq;
            freq.reserve(n - len + 1);
            for (int l = 0; l + len - 1 < n; ++l) {
                ++freq[getHash(l, l + len - 1)];
            }
            for (const auto& [_, cnt] : freq) {
                if (cnt == 1) return true;
            }
            return false;
        };

        int lo = 1, hi = n, ans = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUniqueOfLen(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};