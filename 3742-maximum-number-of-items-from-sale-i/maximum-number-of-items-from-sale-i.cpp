class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        const int MAX_F = 1500;
        
        vector<int> freq(MAX_F + 1, 0);
        int min_price = INT_MAX;
        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }

        vector<int> value(n);
        for (int i = 0; i < n; i++) {
            int f = items[i][0];
            int free_copies = -1;
            for (int multiple = f; multiple <= MAX_F; multiple += f) {
                free_copies += freq[multiple];
            }
            value[i] = 1 + free_copies;
        }

        vector<int> dp(budget + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            int p = items[i][1];
            int v = value[i];
            for (int c = budget; c >= p; c--) {
                if (dp[c - p] != -1) {
                    dp[c] = max(dp[c], dp[c - p] + v);
                }
            }
        }

        int max_copies = 0;
        for (int c = 0; c <= budget; c++) {
            if (dp[c] != -1) {
                max_copies = max(max_copies, dp[c] + (budget - c) / min_price);
            }
        }

        return max_copies;
    }
};