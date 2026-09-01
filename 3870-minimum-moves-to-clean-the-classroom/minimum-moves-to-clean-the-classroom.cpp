class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        int litter_count = 0;
        vector<vector<int>> litter_id(m, vector<int>(n, -1));
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (classroom[r][c] == 'S') {
                    start_r = r;
                    start_c = c;
                } else if (classroom[r][c] == 'L') {
                    litter_id[r][c] = litter_count++;
                }
            }
        }
        
        int target_mask = (1 << litter_count) - 1;
        
        vector<vector<unordered_map<int, int>>> best_energy(m, vector<unordered_map<int, int>>(n));
        
        queue<tuple<int, int, int, int, int>> q;
        
        int initial_mask = target_mask;
        q.push({start_r, start_c, initial_mask, 0, energy});
        best_energy[start_r][start_c][initial_mask] = energy;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [r, c, mask, moves, cur_energy] = q.front();
            q.pop();
            
            if (mask == 0) {
                return moves;
            }
            
            if (cur_energy == 0 && classroom[r][c] != 'R') {
                continue;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                if (classroom[nr][nc] == 'X') continue;
                
                int next_mask = mask;
                if (classroom[nr][nc] == 'L') {
                    int id = litter_id[nr][nc];
                    next_mask &= ~(1 << id);
                }
                
                int next_energy;
                if (classroom[nr][nc] == 'R') {
                    next_energy = energy;
                } else {
                    next_energy = cur_energy - 1;
                }
                
                if (best_energy[nr][nc].count(next_mask) && best_energy[nr][nc][next_mask] >= next_energy) {
                    continue;
                }
                
                best_energy[nr][nc][next_mask] = next_energy;
                q.push({nr, nc, next_mask, moves + 1, next_energy});
            }
        }
        
        return -1;
    }
};