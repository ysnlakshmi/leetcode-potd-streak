#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
private:
    int timer;
    vector<int> tin, tout, depth;
    vector<vector<int>> up;
    vector<int> bit;
    int LOG;

    void bit_update(int idx, int val, int n) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    int point_query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res ^= bit[idx];
        }
        return res;
    }

    void dfs(int u, int p, int current_mask, const string& s, const vector<vector<int>>& adj, vector<int>& initial_a) {
        tin[u] = ++timer;
        up[u][0] = p;
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        int node_mask = 1 << (s[u] - 'a');
        int path_mask = current_mask ^ node_mask;

        initial_a[tin[u]] = path_mask;

        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u, path_mask, s, adj, initial_a);
            }
        }
        tout[u] = timer;
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        for (int i = LOG - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG));
        timer = 0;

        vector<int> initial_a(n + 1, 0);
        dfs(0, 0, 0, s, adj, initial_a);

        bit.assign(n + 2, 0);
        for (int i = 1; i <= n; ++i) {
            int d = initial_a[i] ^ initial_a[i - 1];
            bit_update(i, d, n + 1);
        }

        vector<bool> result;
        vector<char> current_s(s.begin(), s.end());

        for (const string& q_str : queries) {
            stringstream ss(q_str);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                if (current_s[u] != c) {
                    int old_mask = 1 << (current_s[u] - 'a');
                    int new_mask = 1 << (c - 'a');
                    int diff_mask = old_mask ^ new_mask;

                    bit_update(tin[u], diff_mask, n + 1);
                    bit_update(tout[u] + 1, diff_mask, n + 1);
                    current_s[u] = c;
                }
            } else if (type == "query") {
                int u, v;
                ss >> u >> v;

                int lca = get_lca(u, v);

                int mask_u = point_query(tin[u]);
                int mask_v = point_query(tin[v]);
                int lca_node_mask = 1 << (current_s[lca] - 'a');

                int path_mask = mask_u ^ mask_v ^ lca_node_mask;

                bool is_palindrome = (path_mask & (path_mask - 1)) == 0;
                result.push_back(is_palindrome);
            }
        }

        return result;
    }
};