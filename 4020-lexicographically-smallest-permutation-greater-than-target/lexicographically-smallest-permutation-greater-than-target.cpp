class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> orig_count(26, 0);
        for (char c : s) {
            orig_count[c - 'a']++;
        }

        string best_ans = "";

        for (int i = n - 1; i >= 0; --i) {
            vector<int> count = orig_count;
            bool possible_prefix = true;
            
            for (int k = 0; k < i; ++k) {
                if (--count[target[k] - 'a'] < 0) {
                    possible_prefix = false;
                    break;
                }
            }

            if (!possible_prefix) continue;

            for (int c = target[i] - 'a' + 1; c < 26; ++c) {
                if (count[c] > 0) {
                    string res = target.substr(0, i);
                    res += (char)('a' + c);
                    count[c]--;

                    for (int char_idx = 0; char_idx < 26; ++char_idx) {
                        while (count[char_idx] > 0) {
                            res += (char)('a' + char_idx);
                            count[char_idx]--;
                        }
                    }

                    if (best_ans.empty() || res < best_ans) {
                        best_ans = res;
                    }
                    break;
                }
            }
        }

        return best_ans;
    }
};