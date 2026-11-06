class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int q = queries.size();
        vector<pair<int, int>> sorted_queries(q);
        for (int i = 0; i < q; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        sort(sorted_queries.begin(), sorted_queries.end());
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<int> ans(q);
        unordered_map<int, int> active_servers;
        int l = 0, r = 0;
        int m = logs.size();

        for (int i = 0; i < q; ++i) {
            int query_time = sorted_queries[i].first;
            int original_index = sorted_queries[i].second;
            int window_start = query_time - x;
            int window_end = query_time;

            while (r < m && logs[r][1] <= window_end) {
                active_servers[logs[r][0]]++;
                r++;
            }

            while (l < m && logs[l][1] < window_start) {
                int server_id = logs[l][0];
                active_servers[server_id]--;
                if (active_servers[server_id] == 0) {
                    active_servers.erase(server_id);
                }
                l++;
            }

            ans[original_index] = n - active_servers.size();
        }

        return ans;
    }
};