class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;
        vector<int> count(k, 0);
        int maxCount = 0;

        for (int i = 0; i < arrival.size(); ++i) {
            long long currTime = arrival[i];
            long long duration = load[i];

            while (!busy.empty() && busy.top().first <= currTime) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            int preferred = i % k;
            auto it = available.lower_bound(preferred);
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;
            available.erase(it);
            busy.push({currTime + duration, server});
            count[server]++;
            maxCount = max(maxCount, count[server]);
        }

        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == maxCount) {
                result.push_back(i);
            }
        }

        return result;
    }
};