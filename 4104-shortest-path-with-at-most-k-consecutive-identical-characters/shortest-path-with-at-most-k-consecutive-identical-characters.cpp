#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> g(n);
        for (const auto& e : edges) {
            g[e[0]].push_back({e[1], e[2]});
        }
        
        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
        
        dist[0][1] = 0;
        pq.emplace(0, 0, 1);
        
        while (!pq.empty()) {
            auto [d, u, cur] = pq.top();
            pq.pop();
            
            if (u == n - 1) return d;
            if (d > dist[u][cur]) continue;
            
            for (const auto& [v, w] : g[u]) {
                int nxt = (labels[v] != labels[u]) ? 1 : cur + 1;
                if (nxt <= k) {
                    long long nd = d + w;
                    if (nd < dist[v][nxt]) {
                        dist[v][nxt] = nd;
                        pq.emplace(nd, v, nxt);
                    }
                }
            }
        }
        
        return -1;
    }
};