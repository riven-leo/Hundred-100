#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        // 滚动数组
        // +2给当前行开头和结尾增加两个哨兵0，避免边界问题
        // i+1层
        vector<vector<int>> pre(n + 2, vector<int>(n + 2));
        // i层，当前层到最底层两个机器人能摘到的最大樱桃数目
        vector<vector<int>> cur(n + 2, vector<int>(n + 2));

        // 一共走m步
        for (int i = m - 1; i >= 0; i--) {
            // 实际索引是ijk,但是dp索引是ij+1k+1

            // 走了i步,所以j从0开始不会大于i
            for (int j = 0; j < min(n, i + 1); j++) {
                // 走了i步,所以k从n-1开始不会小于n-1-i,同时k不会小于j不然没意义
                for (int k = max(j + 1, n - 1 - i); k < n; k++) {
                    cur[j + 1][k + 1] = max({
                        pre[j][k], pre[j][k + 1], pre[j][k + 2],
                        pre[j + 1][k], pre[j + 1][k + 1], pre[j + 1][k + 2],
                        pre[j + 2][k], pre[j + 2][k + 1], pre[j + 2][k + 2],
                    }) + grid[i][j] + grid[i][k];
                }
            }
            swap(pre, cur); // 下一个 i 的 pre 是 cur
        }
        return pre[1][n];
    }
};
