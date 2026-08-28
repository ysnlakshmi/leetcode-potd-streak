class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++;

        int odd_cnt = 0;
        char mid_char = 0;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                odd_cnt++;
                mid_char = 'a' + i;
            }
        }

        if (odd_cnt > 1) return "";

        vector<int> half_cnt(26, 0);
        for (int i = 0; i < 26; ++i) {
            half_cnt[i] = count[i] / 2;
        }

        int m = n / 2;
        string result = "";

        auto buildPalindrome = [&](const string& half) -> string {
            string full = half;
            if (n % 2 != 0) full += mid_char;
            string rev = half;
            reverse(rev.begin(), rev.end());
            full += rev;
            return full;
        };

        bool can_match_prefix = true;
        vector<int> rem = half_cnt;
        for (int i = 0; i < m; ++i) {
            int idx = target[i] - 'a';
            if (rem[idx] > 0) {
                rem[idx]--;
            } else {
                can_match_prefix = false;
                break;
            }
        }

        if (can_match_prefix) {
            string exact_half = target.substr(0, m);
            string full = buildPalindrome(exact_half);
            if (full > target) {
                result = full;
            }
        }

        for (int i = m - 1; i >= 0; --i) {
            vector<int> avail = half_cnt;
            bool valid_prefix = true;
            for (int k = 0; k < i; ++k) {
                int idx = target[k] - 'a';
                if (avail[idx] > 0) {
                    avail[idx]--;
                } else {
                    valid_prefix = false;
                    break;
                }
            }
            if (!valid_prefix) continue;

            for (int c = (target[i] - 'a') + 1; c < 26; ++c) {
                if (avail[c] > 0) {
                    string prefix = target.substr(0, i);
                    prefix += (char)('a' + c);
                    avail[c]--;

                    for (int ch = 0; ch < 26; ++ch) {
                        while (avail[ch] > 0) {
                            prefix += (char)('a' + ch);
                            avail[ch]--;
                        }
                    }

                    string candidate = buildPalindrome(prefix);
                    if (result.empty() || candidate < result) {
                        result = candidate;
                    }
                    break;
                }
            }
        }

        return result;
    }
};