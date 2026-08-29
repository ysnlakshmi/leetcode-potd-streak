class Solution {
public:
    std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums, int limit) {
        int n = nums.size();
        
        std::vector<std::pair<int, int>> sorted_nums(n);
        for (int i = 0; i < n; ++i) {
            sorted_nums[i] = {nums[i], i};
        }
        
        std::sort(sorted_nums.begin(), sorted_nums.end());
        
        std::vector<int> result(n);
        
        int i = 0;
        while (i < n) {
            int j = i;
            while (j + 1 < n && sorted_nums[j + 1].first - sorted_nums[j].first <= limit) {
                j++;
            }
            
            std::vector<int> indices;
            for (int k = i; k <= j; ++k) {
                indices.push_back(sorted_nums[k].second);
            }
            
            std::sort(indices.begin(), indices.end());
            
            for (int k = 0; k < indices.size(); ++k) {
                result[indices[k]] = sorted_nums[i + k].first;
            }
            
            i = j + 1;
        }
        
        return result;
    }
};