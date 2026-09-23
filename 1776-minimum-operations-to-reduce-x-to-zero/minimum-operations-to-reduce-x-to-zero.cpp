class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        long long totalSum = 0;
        
        for (int num : nums) {
            totalSum += num;
        }
        
        long long target = totalSum - x;
        if (target < 0) return -1;
        if (target == 0) return n;
        
        int maxLen = -1;
        long long currentSum = 0;
        int left = 0;
        
        for (int right = 0; right < n; ++right) {
            currentSum += nums[right];
            while (currentSum > target && left <= right) {
                currentSum -= nums[left];
                left++;
            }
            if (currentSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }
        
        return maxLen == -1 ? -1 : n - maxLen;
    }
};