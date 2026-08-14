#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // pre/cur 的两个下标分别是两台机器人的列；左右补边避免 9 个转移逐个判越界。
        vector<vector<int>> pre(n + 2, vector<int>(n + 2));
        vector<vector<int>> cur(n + 2, vector<int>(n + 2));
        for (int i = m - 1; i >= 0; i--) {
            // j、k 只枚举从两端出发走到第 i 行后可能到达的位置，并保持 j < k。
            for (int j = 0; j < min(n, i + 1); j++) {
                for (int k = max(j + 1, n - 1 - i); k < n; k++) {
                    // 两台机器人下一步各有左/中/右 3 种选择，共 9 个后继状态。
                    cur[j + 1][k + 1] = max({
                        pre[j][k], pre[j][k + 1], pre[j][k + 2],
                        pre[j + 1][k], pre[j + 1][k + 1], pre[j + 1][k + 2],
                        pre[j + 2][k], pre[j + 2][k + 1], pre[j + 2][k + 2],
                    }) + grid[i][j] + grid[i][k];
                }
            }
            swap(pre, cur); // 易错：交换后 pre 才代表刚算完的当前行。
        }
        // 补边后，起始列 0 和 n-1 对应下标 1 和 n。
        return pre[1][n];
    }
};
