class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);
        
        for (int i = 0; i < n; ++i) {
            squares[i] = 1LL * nums[i] * nums[i];
        }
        
        sort(squares.begin(), squares.end());
        
        long long score = 0;
        int m = n / 2;
        
        for (int i = 0; i < m; ++i) {
            score -= squares[i];
        }
        for (int i = m; i < n; ++i) {
            score += squares[i];
        }
        
        return score;
    }
};