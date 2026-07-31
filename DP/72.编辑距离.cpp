#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 二、1:1 翻译成递推
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
    int dfs(int i, int j) {
        vector<vector<int>> memo(n, vector<int>(m, -1));
        if (i == n) return m - j;
        if (j == m) return n - i;
        if (w1[i] == w2[j]) return dfs(i+1, j+1);
        int deletecost = dfs(i+1, j);
        int insertcost = dfs(i, j+1);
        int replacecost = dfs(i+1, j+1);
        return 1 + min(dfs(i, j+1), dfs(i+1, j), dfs(i+1, j+1));
    }
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        return dfs(0,0);
    }
};

// 一、递归搜索 + 保存计算结果 = 记忆化搜索
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

