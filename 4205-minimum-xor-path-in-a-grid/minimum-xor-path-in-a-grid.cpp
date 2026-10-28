#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<bitset<1024>>> dp(m, vector<bitset<1024>>(n));
        dp[0][0].set(grid[0][0]);
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;
                
                bitset<1024> reachable;
                if (i > 0) reachable |= dp[i - 1][j];
                if (j > 0) reachable |= dp[i][j - 1];
                
                for (int v = 0; v < 1024; ++v) {
                    if (reachable[v]) {
                        dp[i][j].set(v ^ grid[i][j]);
                    }
                }
            }
        }
        
        for (int v = 0; v < 1024; ++v) {
            if (dp[m - 1][n - 1][v]) {
                return v;
            }
        }
        
        return 0;
    }
};