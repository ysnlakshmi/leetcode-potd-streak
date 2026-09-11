class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        vector<int> count(10, 0);
        for (int d : digits) {
            count[d]++;
        }

        int ans = 0;
        for (int num = 100; num <= 999; num += 2) {
            int d1 = num / 100;
            int d2 = (num / 10) % 10;
            int d3 = num % 10;

            vector<int> freq(10, 0);
            freq[d1]++;
            freq[d2]++;
            freq[d3]++;

            bool possible = true;
            for (int i = 0; i < 10; i++) {
                if (freq[i] > count[i]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                ans++;
            }
        }

        return ans;
    }
};