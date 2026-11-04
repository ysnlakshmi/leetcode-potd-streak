#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> minOps = getMinOps(nums, x);
        
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, 1e18));
        
        for (int i = 0; i <= n; ++i) {
            dp[0][i] = 0;
        }
        
        for (int j = 1; j <= k; ++j) {
            for (int i = 1; i <= n; ++i) {
                dp[j][i] = dp[j][i - 1];
                if (i >= x) {
                    long long cost = minOps[i - x];
                    dp[j][i] = min(dp[j][i], dp[j - 1][i - x] + cost);
                }
            }
        }
        
        return dp[k][n];
    }

private:
    vector<long long> getMinOps(const vector<int>& nums, int x) {
        vector<long long> minOps;
        multiset<long long> lower;
        multiset<long long> upper;
        long long lowerSum = 0;
        long long upperSum = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }
            
            if (i >= x) {
                long long outNum = nums[i - x];
                auto it = lower.find(outNum);
                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= outNum;
                } else {
                    upper.erase(upper.find(outNum));
                    upperSum -= outNum;
                }
            }
            
            if (lower.size() < upper.size()) {
                long long val = *upper.begin();
                upper.erase(upper.begin());
                lower.insert(val);
                upperSum -= val;
                lowerSum += val;
            } else if (lower.size() - upper.size() > 1) {
                long long val = *lower.rbegin();
                lower.erase(prev(lower.end()));
                upper.insert(val);
                lowerSum -= val;
                upperSum += val;
            }
            
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long ops = (median * lower.size() - lowerSum) + (upperSum - median * upper.size());
                minOps.push_back(ops);
            }
        }
        
        return minOps;
    }
};