class Solution {
public:
    long long lcm(long long a, long long b) {
        return (a / std::gcd(a, b)) * b;
    }

    long long countMultiples(long long m, const std::vector<int>& coins) {
        int n = coins.size();
        long long total = 0;
        
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long current_lcm = 1;
            int bits = 0;
            
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    bits++;
                    current_lcm = lcm(current_lcm, coins[i]);
                    if (current_lcm > m) break;
                }
            }
            
            if (current_lcm <= m) {
                if (bits % 2 == 1) {
                    total += m / current_lcm;
                } else {
                    total -= m / current_lcm;
                }
            }
        }
        
        return total;
    }

    long long findKthSmallest(std::vector<int>& coins, int k) {
        long long min_coin = *std::min_element(coins.begin(), coins.end());
        long long low = 1;
        long long high = min_coin * (long long)k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            
            if (countMultiples(mid, coins) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};