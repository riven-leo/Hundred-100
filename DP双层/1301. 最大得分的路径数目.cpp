#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using PII = pair<int, int>;

class Solution {
private:
    static constexpr int mod = (int)1e9 + 7;

public:
    // 用后继状态更新当前格：更高分则整体覆盖，同分才累加方案数。
    void update(vector<vector<PII>>& dp, int n, int x, int y, int u, int v) {
        // 越界或不可达状态不能参与转移。
        if (u >= n || v >= n || dp[u][v].first == -1) {
            return;
        }
        if (dp[u][v].first > dp[x][y].first) {
            dp[x][y] = dp[u][v];
        }
        else if (dp[u][v].first == dp[x][y].first) {
            dp[x][y].second += dp[u][v].second;
            if (dp[x][y].second >= mod) {
                dp[x][y].second -= mod;
            }
        }
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        // first=最大得分，second=达到最大得分的方案数；{-1,0} 表示不可达。
        vector<vector<PII>> dp(n, vector<PII>(n, {-1, 0}));
        // 终点本身不计分，但有一条合法的空路径。
        dp[n - 1][n - 1] = {0, 1};
        // 当前格依赖下、右、右下，因此必须从右下向左上递推。
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (!(i == n - 1 && j == n - 1) && board[i][j] != 'X') {
                    update(dp, n, i, j, i + 1, j);
                    update(dp, n, i, j, i, j + 1);
                    update(dp, n, i, j, i + 1, j + 1);
                    if (dp[i][j].first != -1) {
                        // 起点 E 不计分；只有可达格才能在最优后继上增加当前分数。
                        dp[i][j].first += (board[i][j] == 'E' ? 0 : board[i][j] - '0');
                    }
                }
            }
        }
        return dp[0][0].first == -1 ? vector<int>{0, 0} : vector<int>{dp[0][0].first, dp[0][0].second};
    }
};
