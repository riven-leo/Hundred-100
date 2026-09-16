#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int id = 2;
        // 岛屿编号从2开始
        vector<int> area(n*m+2, 0);
        int ans = 0;

        auto dfs = [&](this auto&& dfs, int i, int j, int id) -> int {
            // if 点不是0 就归属岛屿id
            if (grid[i][j] != 1) return 0;
            grid[i][j] = id;

            // DFS找出岛屿总面积
            int cnt = 1;
            if (j-1 >= 0) cnt += dfs(i, j-1, id);
            if (j+1 < m) cnt += dfs(i, j+1, id);
            if (i-1 >= 0) cnt += dfs(i-1, j, id);
            if (i+1 < n) cnt += dfs(i+1, j, id);
            return cnt;
        };

        // 预处理岛屿，给岛屿编号
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m; j++) {
                // 是1就开始搜索，把岛屿都标记
                if (grid[i][j] == 1) {
                    area[id] = dfs(i, j, id);

                    // 解决全1的情况
                    ans = max(ans, area[id]);
                    id++;
                }
            }

        // 翻转0，进行合并岛屿
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 反转0，开始搜索
                if (grid[i][j] == 0) {

                    // 防止重复计算同一个岛屿
                    unordered_set<int> is;
                    if (j-1 >= 0) is.insert(grid[i][j-1]);
                    if (j+1 < m) is.insert(grid[i][j+1]);
                    if (i-1 >= 0) is.insert(grid[i-1][j]);
                    if (i+1 < n) is.insert(grid[i+1][j]);
                    
                    // 0反转为1后岛屿总面积
                    int cnt = 1;
                    for (int id: is) cnt += area[id];

                    // 每个0都有个面积，找出最大的
                    ans = max(ans, cnt);
                }
            }
        }
        return ans;
    }
};
