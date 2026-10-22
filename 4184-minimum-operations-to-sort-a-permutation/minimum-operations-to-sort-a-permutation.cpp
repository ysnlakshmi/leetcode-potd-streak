class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }
        
        int ans = 1e9;
        
        auto check = [&](int step) {
            for (int i = 1; i < n; ++i) {
                int prev = (zero + (i - 1) * step) % n;
                if (prev < 0) prev += n;
                int curr = (zero + i * step) % n;
                if (curr < 0) curr += n;
                if (nums[prev] > nums[curr]) {
                    return false;
                }
            }
            return true;
        };
        
        if (check(1)) {
            ans = min(ans, zero);
            ans = min(ans, n - zero + 2);
        }
        
        if (check(-1)) {
            ans = min(ans, zero + 2);
            ans = min(ans, n - zero);
        }
        
        return ans > 1e8 ? -1 : ans;
    }
};