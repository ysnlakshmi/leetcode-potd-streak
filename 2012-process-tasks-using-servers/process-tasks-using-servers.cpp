class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> free_servers;
        for (int i = 0; i < n; ++i) {
            free_servers.push({servers[i], i});
        }
        
        priority_queue<array<long long, 3>, vector<array<long long, 3>>, greater<array<long long, 3>>> busy_servers;
        
        vector<int> ans(m);
        long long current_time = 0;
        
        for (int j = 0; j < m; ++j) {
            current_time = max(current_time, (long long)j);
            
            while (!busy_servers.empty() && busy_servers.top()[0] <= current_time) {
                auto [free_time, weight, index] = busy_servers.top();
                busy_servers.pop();
                free_servers.push({(int)weight, (int)index});
            }
            
            if (free_servers.empty()) {
                current_time = busy_servers.top()[0];
                while (!busy_servers.empty() && busy_servers.top()[0] <= current_time) {
                    auto [free_time, weight, index] = busy_servers.top();
                    busy_servers.pop();
                    free_servers.push({(int)weight, (int)index});
                }
            }
            
            auto [weight, index] = free_servers.top();
            free_servers.pop();
            
            ans[j] = index;
            busy_servers.push({current_time + tasks[j], weight, index});
        }
        
        return ans;
    }
};