class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        
        long long totalSum = 0;
        
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;
            
            bool possible = true;
            for (int i = 0; i < n; i += k) {
                int drops = 0;
                int drop_idx = -1;
                for (int j = 0; j < k; ++j) {
                    int curr = nums[i + j];
                    int next = nums[i + (j + 1) % k];
                    if (curr > next) {
                        drops++;
                        drop_idx = j;
                    }
                }
                if (drops > 1) {
                    possible = false;
                    break;
                }
                
                int start = (drops == 0) ? 0 : (drop_idx + 1);
                bool match = true;
                for (int j = 0; j < k; ++j) {
                    if (nums[i + (start + j) % k] != sorted_nums[i + j]) {
                        match = false;
                        break;
                    }
                }
                if (!match) {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                totalSum += k;
            }
        }
        
        return totalSum;
    }
};