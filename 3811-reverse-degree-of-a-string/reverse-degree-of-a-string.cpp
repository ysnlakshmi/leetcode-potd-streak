class Solution {
public:
    int reverseDegree(string s) {
        int totalDegree = 0;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            int revAlpha = 26 - (s[i] - 'a');
            int strIndex = i + 1;
            totalDegree += revAlpha * strIndex;
        }
        return totalDegree;
    }
};