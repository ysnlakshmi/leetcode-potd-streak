class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> map;
        for (const auto& pair : knowledge) {
            map[pair[0]] = pair[1];
        }

        string result = "";
        result.reserve(s.size());
        
        int n = s.length();
        for (int i = 0; i < n; ) {
            if (s[i] == '(') {
                int j = i + 1;
                while (j < n && s[j] != ')') {
                    j++;
                }
                string key = s.substr(i + 1, j - i - 1);
                if (map.count(key)) {
                    result += map[key];
                } else {
                    result += "?";
                }
                i = j + 1;
            } else {
                result += s[i];
                i++;
            }
        }
        
        return result;
    }
};