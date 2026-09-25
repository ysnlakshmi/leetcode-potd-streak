class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> res = parse(expression);
        return vector<string>(res.begin(), res.end());
    }

private:
    set<string> parse(string exp) {
        int level = 0;
        vector<string> parts;
        string current = "";
        for (char c : exp) {
            if (c == '{') level++;
            else if (c == '}') level--;
            
            if (c == ',' && level == 0) {
                parts.push_back(current);
                current = "";
            } else {
                current += c;
            }
        }
        parts.push_back(current);
        
        if (parts.size() > 1) {
            set<string> result;
            for (const string& part : parts) {
                set<string> sub = parse(part);
                result.insert(sub.begin(), sub.end());
            }
            return result;
        }
        vector<string> factors;
        int i = 0, n = exp.size();
        while (i < n) {
            if (exp[i] == '{') {
                int start = i;
                int l_cnt = 0;
                while (i < n) {
                    if (exp[i] == '{') l_cnt++;
                    else if (exp[i] == '}') l_cnt--;
                    i++;
                    if (l_cnt == 0) break;
                }
                factors.push_back(exp.substr(start, i - start));
            } else {
                string word = "";
                while (i < n && isalpha(exp[i])) {
                    word += exp[i++];
                }
                if (!word.empty()) {
                    factors.push_back(word);
                }
            }
        }
        
        if (factors.size() > 1) {
            set<string> result = {""};
            for (const string& factor : factors) {
                set<string> sub = parse(factor);
                set<string> next_result;
                for (const string& s1 : result) {
                    for (const string& s2 : sub) {
                        next_result.insert(s1 + s2);
                    }
                }
                result = next_result;
            }
            return result;
        }
        if (!exp.empty() && exp.front() == '{' && exp.back() == '}') {
            return parse(exp.substr(1, exp.size() - 2));
        }
        
        return {exp};
    }
};