class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pairIndex(n);
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pairIndex[j] = i;
                pairIndex[i] = j;
            }
        }

        string result = "";
        int i = 0, dir = 1;
        while (i < n) {
            if (s[i] == '(' || s[i] == ')') {
                i = pairIndex[i];
                dir = -dir;
            } else {
                result += s[i];
            }
            i += dir;
        }

        return result;
    }
};