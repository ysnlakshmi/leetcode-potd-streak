#include <vector>
#include <unordered_map>

class Solution {
public:
    int sumCounts(std::vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        
        for (int i = 0; i < n; ++i) {
            std::unordered_map<int, int> freq;
            for (int j = i; j < n; ++j) {
                freq[nums[j]]++;
                int distinctCount = freq.size();
                result += distinctCount * distinctCount;
            }
        }
        
        return result;
    }
};