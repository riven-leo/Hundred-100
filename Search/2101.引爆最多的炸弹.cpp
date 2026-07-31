#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
    public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        int ans = 1;
        vector<vector<int>> g(n);
        vector<int> vis(n,0);
        
        // 把炸弹和炸弹之间的引爆关系变成有向图
        for (int i = 0; i < n; i++) {
            long long xi = bombs[i][0];
            long long yi = bombs[i][1];
            long long zi = bombs[i][2];
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                long long xj = bombs[j][0];
                long long yj = bombs[j][1];

                // 半径包含炸弹原点位置
                if (zi*zi >= (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)){
                    g[i].push_back(j);
                }
            }
        }
        
        // 搜索每个炸弹最多能引爆多少个炸弹
        auto dfs = [&](this auto&& dfs, int x) -> int {
            vis[x] = 1;
            int cnt = 1;
            for (int t : g[x]) {
                if (vis[t] != 1) cnt += dfs(t);
            }
            return cnt;
        };

        // 遍历每个炸弹
        for (int i = 0; i < n; i++) {
            fill(vis.begin(), vis.end(), 0);
            ans = max(ans, dfs(i)); // 单次 DFS：O(N+E)，E=O(N2)
        }
        return ans;
    }
};
