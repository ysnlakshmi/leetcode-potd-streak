#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int max_val = *max_element(nums.begin(), nums.end());
        int moves = 0;
        
        for (int num : nums) {
            moves += max_val - num;
        }
        
        return moves;
    }
};