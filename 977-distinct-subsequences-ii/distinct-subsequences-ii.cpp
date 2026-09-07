class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        vector<long> dp(26, 0);
        long ans = 0;
        
        for (char c : s) {
            int i = c - 'a';
            long add = (ans - dp[i] + 1 + MOD) % MOD;
            
            ans = (ans + add) % MOD;
            
            dp[i] = (dp[i] + add) % MOD;
        }
        
        return ans;
    }
};