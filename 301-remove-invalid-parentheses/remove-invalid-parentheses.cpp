class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        if (s.empty()) return {""};
        
        unordered_set<string> visited;
        queue<string> q;
        
        q.push(s);
        visited.insert(s);
        
        bool found = false;
        
        while (!q.empty()) {
            int size = q.size();
            unordered_set<string> level_res;
            
            for (int i = 0; i < size; ++i) {
                string curr = q.front();
                q.pop();
                
                if (isValid(curr)) {
                    level_res.insert(curr);
                    found = true;
                }
                
                if (found) continue;
                
                for (int j = 0; j < curr.length(); ++j) {
                    if (curr[j] != '(' && curr[j] != ')') continue;
                    string next = curr.substr(0, j) + curr.substr(j + 1);
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
            
            if (found) {
                return vector<string>(level_res.begin(), level_res.end());
            }
        }
        
        return {""};
    }

private:
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                if (count < 0) return false;
            }
        }
        return count == 0;
    }
};