class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<long long> dp(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            long long min_cost = -1;
            int start = max(0, i - 3);
            
            for (int j = start; j < i; ++j) {
                long long cost = dp[j] + costs[i - 1] + (long long)(i - j) * (i - j);
                if (min_cost == -1 || cost < min_cost) {
                    min_cost = cost;
                }
            }
            dp[i] = min_cost;
        }
        
        return dp[n];
    }
};