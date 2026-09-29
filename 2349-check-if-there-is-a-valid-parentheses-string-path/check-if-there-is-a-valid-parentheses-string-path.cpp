class Solution {
private:
    int m, n;
    vector<vector<vector<int>>> memo;
    bool dfs(int i, int j, int k, vector<vector<char>>& grid) {
        if (i >= m || j >= n) return false;
        k += (grid[i][j] == '(' ? 1 : -1);
        if (k < 0 || k > (m - i + n - j - 1)) return false;
        if (i == m - 1 && j == n - 1) {
            return k == 0;
        }
        if (memo[i][j][k] != -1) {
            return memo[i][j][k];
        }
        bool down = dfs(i + 1, j, k, grid);
        bool right = dfs(i, j + 1, k, grid);
        return memo[i][j][k] = (down || right);
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(' || (m + n - 1) % 2 != 0) {
            return false;
        }

        memo = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m + n + 1, -1)));

        return dfs(0, 0, 0, grid);
    }
};