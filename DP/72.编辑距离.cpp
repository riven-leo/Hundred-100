#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 递推
class Solution {
public:
    int minDistance(string w1, string w2) {
        int n = w1.size();
        int m = w2.size();

        vector f(n + 1, vector<int>(m + 1, -1));

        // 处理w1空和w2空两种特殊情况
        for (int i = 1; i <= n; i++) {
            f[i][0] = i;
        }
        for (int j = 1; j <= m; j++) {
            f[0][j] = j;
        }

        // 从头开始比较
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                f[i + 1][j + 1] =
                    w1[i] == w2[j] ? 
                    f[i][j] : 1 + min({f[i + 1][j], f[i][j + 1], f[i][j]});
            }
        }
        return f[n][m];
    }
};

class Solution {
public:
    int minDistance(string w1, string w2) {
        /*状态(子问题)：1.从0到i的前缀变成从0到j的前缀需要多少步
        i+1j+1 = w1i == w2j ? ij : 1 + min 
        2.从i开始的后缀变成从j开始的后缀需要多少步
        状态(子问题)转移：ij = 1 + min ij+1, i+1j, i+1j+1

        处理w1 or w2 为空的情况
        如果w1i == w2j, ij = i+1j+1
        */
        int n = w1.size(), m = w2.size();
        vector f(n+1, vector<int>(m+1));

        // w2 is empty, 从m到m是空的
        for (int i = 0; i < n; i ++) {
            f[i][m] = n-i;
        }
        // w1 is empty
        for (int j = 0; j < m; j ++) {
            f[n][j] = m-j;
        }
        // 从最后往前DP
        for (int i = n-1; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                f[i][j] = 
                    w1[i] == w2[j]?
                    f[i+1][j+1]:
                    1 + min({f[i+1][j], f[i][j+1], f[i+1][j+1]});
            }
        }
        return f[0][0];
    }
};


// 记忆化递归搜索
class Solution {
public:
    int minDistance(string w1, string w2) {
        int n = w1.size();
        int m = w2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));

        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i == n) return m - j;
            if (j == m) return n - i;

            if (memo[i][j] != -1) 
                return memo[i][j];

            if (w1[i] == w2[j]) 
                return memo[i][j] = dfs(i+1, j+1);

            return memo[i][j] = 1 + min({dfs(i, j+1), dfs(i+1, j), dfs(i+1, j+1)});
        };

        return dfs(0,0);
    }
};

