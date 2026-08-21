#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        constexpr int MOD = 1'000'000'007;
        int m = board.size(), n = board[0].size();
        vector max_sum(m + 1, vector<int>(n + 1, INT_MIN)); // 定义同 64 题（改成最大路径和）
        vector ways(m + 1, vector<int>(n + 1)); // 定义同 63 题

        // 从E走到(0,0)得分最大值和最大得分的方案数
        max_sum[0][0] = 0;
        ways[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char ch = board[i][j];
                if (ch == 'X') {
                    continue;
                }
                // 左上、正上、正左
                max_sum[i + 1][j + 1] = 
                max({max_sum[i][j], max_sum[i][j + 1], max_sum[i + 1][j]});
                
                int s = max_sum[i + 1][j + 1];
                long long w = 0;
                // 如果路径和相同，则累加方案数（加法原理）
                if (max_sum[i][j] == s) {
                    w += ways[i][j];
                }
                if (max_sum[i][j + 1] == s) {
                    w += ways[i][j + 1];
                }
                if (max_sum[i + 1][j] == s) {
                    w += ways[i + 1][j];
                }
                ways[i + 1][j + 1] = w % MOD;

                if ('1' <= ch && ch <= '9') {
                    max_sum[i + 1][j + 1] += ch - '0'; // 加上当前格子的值
                }
            }
        }

        return max_sum[m][n] < 0 ? vector{0, 0} : vector{max_sum[m][n], ways[m][n]};
    }
};


