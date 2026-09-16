#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& D) {
        int n = D.size();
        int m = D[0].size();
        vector dp(n, vector<int>(m));

        // 初始化第一点
        dp[n-1][m-1] = max(1, 1 - D[n-1][m-1]);

        // 预处理最后一行和最后一列
        for (int i = n-2; i >= 0; i--) 
            dp[i][m-1] = max(1, dp[i+1][m-1] - D[i][m-1]);
        for (int j = m-2; j >= 0; j--) 
            dp[n-1][j] = max(1, dp[n-1][j+1] - D[n-1][j]);

        // 递推计算中间
        for (int i = n-2; i >= 0; i--) 
            for (int j = m-2; j >= 0; j--) 
                dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - D[i][j]);

        return dp[0][0];
    }
};