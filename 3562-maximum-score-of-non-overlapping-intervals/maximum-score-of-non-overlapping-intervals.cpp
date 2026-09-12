class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<long long>> augmented(n, vector<long long>(4));
        for (int i = 0; i < n; ++i) {
            augmented[i][0] = intervals[i][0];
            augmented[i][1] = intervals[i][1];
            augmented[i][2] = intervals[i][2];
            augmented[i][3] = i;
        }

        sort(augmented.begin(), augmented.end(), [](const vector<long long>& a, const vector<long long>& b) {
            if (a[1] != b[1]) return a[1] < b[1];
            if (a[0] != b[0]) return a[0] < b[0];
            return a[3] < b[3];
        });

        vector<vector<pair<long long, vector<int>>>> dp(n, vector<pair<long long, vector<int>>>(5, {0LL, {}}));

        dp[0][1] = {augmented[0][2], {(int)augmented[0][3]}};
        long long max_weight = augmented[0][2];

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= 4; ++j) {
                dp[i][j] = dp[i - 1][j];
            }

            int low = 0, high = i - 1, idx = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (augmented[mid][1] < augmented[i][0]) {
                    idx = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            for (int j = 1; j <= 4; ++j) {
                long long cur_weight = augmented[i][2];
                vector<int> cur_indices = {(int)augmented[i][3]};

                if (idx != -1 && j > 1) {
                    cur_weight += dp[idx][j - 1].first;
                    if (dp[idx][j - 1].first > 0) {
                        cur_indices.insert(cur_indices.end(), dp[idx][j - 1].second.begin(), dp[idx][j - 1].second.end());
                        sort(cur_indices.begin(), cur_indices.end());
                    } else {
                        continue;
                    }
                } else if (j > 1) {
                    continue;
                }

                if (cur_weight > dp[i][j].first || 
                    (cur_weight == dp[i][j].first && !dp[i][j].second.empty() && cur_indices < dp[i][j].second)) {
                    dp[i][j] = {cur_weight, cur_indices};
                }
            }
        }

        long long best_weight = -1;
        vector<int> best_indices;

        for (int j = 1; j <= 4; ++j) {
            long long w = dp[n - 1][j].first;
            if (w > best_weight) {
                best_weight = w;
                best_indices = dp[n - 1][j].second;
            } else if (w == best_weight && !dp[n - 1][j].second.empty()) {
                if (best_indices.empty() || dp[n - 1][j].second < best_indices) {
                    best_indices = dp[n - 1][j].second;
                }
            }
        }

        sort(best_indices.begin(), best_indices.end());
        return best_indices;
    }
};