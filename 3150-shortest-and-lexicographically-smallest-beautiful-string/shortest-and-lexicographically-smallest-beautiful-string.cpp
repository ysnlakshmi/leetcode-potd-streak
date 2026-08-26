class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> ones;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '1') {
                ones.push_back(i);
            }
        }
        
        if (ones.size() < k) {
            return "";
        }
        
        string result = "";
        int min_len = s.length() + 1;
        
        for (int i = 0; i + k - 1 < ones.size(); ++i) {
            int start = ones[i];
            int end = ones[i + k - 1];
            int len = end - start + 1;
            
            string sub = s.substr(start, len);
            
            if (len < min_len) {
                min_len = len;
                result = sub;
            } else if (len == min_len) {
                if (sub < result) {
                    result = sub;
                }
            }
        }
        
        return result;
    }
};