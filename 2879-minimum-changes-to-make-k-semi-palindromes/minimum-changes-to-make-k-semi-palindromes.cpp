#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        
        vector<vector<int>> cost(n, vector<int>(n, 1e9));
        
        vector<vector<int>> divisors(n + 1);
        for (int len = 1; len <= n; ++len) {
            for (int d = 1; d < len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                }
            }
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int len = j - i + 1;
                if (len == 1) {
                    continue;
                }
                int min_cost = 1e9;
                
                for (int d : divisors[len]) {
                    int changes = 0;
                    for (int offset = 0; offset < d; ++offset) {
                        int left = i + offset;
                        int right = j - (d - 1 - offset);
                        while (left < right) {
                            if (s[left] != s[right]) {
                                changes++;
                            }
                            left += d;
                            right -= d;
                        }
                    }
                    min_cost = min(min_cost, changes);
                }
                cost[i][j] = min_cost;
            }
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 1e9));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int h = j - 1; h < i; ++h) {
                    if (h == 0) {
                        dp[i][j] = min(dp[i][j], cost[0][i - 1]);
                    } else {
                        if (dp[h][j - 1] != 1e9 && cost[h][i - 1] != 1e9) {
                            dp[i][j] = min(dp[i][j], dp[h][j - 1] + cost[h][i - 1]);
                        }
                    }
                }
            }
        }
        
        return dp[n][k];
    }
};