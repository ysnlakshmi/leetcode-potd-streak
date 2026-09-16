class Solution {
public:
    int numberOfSets(int n, int k) {
        long long MOD = 1e9 + 7;
        
        vector<vector<long long>> f(n + 1, vector<long long>(k + 1, 0));
        vector<vector<long long>> g(n + 1, vector<long long>(k + 1, 0));
        
        f[1][0] = 1;
        
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                f[i][j] = (f[i-1][j] + g[i-1][j]) % MOD;
                
                g[i][j] = g[i-1][j];
                if (j > 0) {
                    g[i][j] = (g[i][j] + f[i-1][j-1] + g[i-1][j-1]) % MOD;
                }
            }
        }
        
        return (f[n][k] + g[n][k]) % MOD;
    }
};