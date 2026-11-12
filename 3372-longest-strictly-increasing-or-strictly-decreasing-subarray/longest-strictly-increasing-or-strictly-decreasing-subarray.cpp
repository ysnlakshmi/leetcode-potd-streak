class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        if (nums.empty()) return 0;

        int ans = 1;
        int cnt1 = 1;
        int cnt2 = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                cnt1++;
                cnt2 = 1;
            } else if (nums[i] < nums[i - 1]) {
                cnt2++;
                cnt1 = 1;
            } else {
                cnt1 = 1;
                cnt2 = 1;
            }
            ans = max({ans, cnt1, cnt2});
        }

        return ans;
    }
};