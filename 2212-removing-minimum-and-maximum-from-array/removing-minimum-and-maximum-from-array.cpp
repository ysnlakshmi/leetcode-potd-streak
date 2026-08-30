class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;

        int minIdx = 0, maxIdx = 0;
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] < nums[minIdx]) minIdx = i;
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }

        if (minIdx > maxIdx) {
            swap(minIdx, maxIdx);
        }

        int op1 = maxIdx + 1;
        int op2 = n - minIdx;
        int op3 = (minIdx + 1) + (n - maxIdx);

        return min({op1, op2, op3});
    }
};