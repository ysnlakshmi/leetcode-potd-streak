class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const vector<int> primes = {2, 3, 5, 7};
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                bool valid = true;

                for (int p : primes) {
                    int sumExp = 0;
                    int minExp = INT_MAX;
                    int maxExp = 0;

                    for (int k = i; k <= j; ++k) {
                        int x = nums[k];
                        int cnt = 0;
                        while (x % p == 0) {
                            ++cnt;
                            x /= p;
                        }
                        sumExp += cnt;
                        minExp = min(minExp, cnt);
                        maxExp = max(maxExp, cnt);
                    }

                    if (sumExp != minExp + maxExp) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};