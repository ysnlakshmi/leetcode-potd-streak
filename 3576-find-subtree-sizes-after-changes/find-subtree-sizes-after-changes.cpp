#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = static_cast<int>(parent.size());
        vector<vector<int>> orig_adj(n);
        for (int i = 1; i < n; ++i) {
            orig_adj[parent[i]].push_back(i);
        }

        vector<int> new_parent = parent;
        vector<int> last_char(26, -1);

        auto find_new_parents = [&](auto& self, int u) -> void {
            int c = s[u] - 'a';
            if (last_char[c] != -1) {
                new_parent[u] = last_char[c];
            }

            int prev = last_char[c];
            last_char[c] = u;

            for (int v : orig_adj[u]) {
                self(self, v);
            }

            last_char[c] = prev;
        };

        find_new_parents(find_new_parents, 0);

        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            new_adj[new_parent[i]].push_back(i);
        }

        vector<int> ans(n, 0);
        auto calc_sizes = [&](auto& self, int u) -> int {
            int sz = 1;
            for (int v : new_adj[u]) {
                sz += self(self, v);
            }
            return ans[u] = sz;
        };

        calc_sizes(calc_sizes, 0);
        return ans;
    }
};