class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        /*状态：从ij到E的最大得分和方案数
        状态转移：ij = max i-1j-1, i-1j, ij-1
        大小n+1m+1将结果向右移动避免边界问题,赋值最大负数判断没有路径
        初始化为0和1
        从E(0,0)开始递推循环,到n+1m+1结束：
            如果当前值为'x'跳过
            状态转移
            找出前驱是谁，则加上前驱的ways
            mod 1e9+7
            如果ij是1~9则加上
        return nm的最大得分和方案数，如果nm最大得分小于0，返回[00]*/
        constexpr int MOD = 1'000'000'007;
        int n = board.size(), m = board[0].size();
        // 利用n+1m+1,把max_num和ways第0行和第0列,变成虚拟边界赋值-∞
        // borad[0][0]对应max_num[1][1]ways[1][1]
        vector max_num(n+1, vector<int>(m+1, INT_MIN));
        vector ways(n+1, vector<int>(m+1));
        max_num[0][0] = 0;
        ways[0][0] = 1;

        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j++) {
                char ch = board[i][j];
                if (ch == 'X') continue;
                max_num[i+1][j+1] = 
                    max({max_num[i][j], max_num[i][j+1], max_num[i+1][j]});
                int s = max_num[i+1][j+1];
                long long w = 0; 
                if (max_num[i][j] == s) w += ways[i][j];
                if (max_num[i][j+1] == s) w += ways[i][j+1];
                if (max_num[i+1][j] == s) w += ways[i+1][j];
                ways[i+1][j+1] = w % MOD;
                if ('1' <= ch && ch <= '9') 
                    max_num[i+1][j+1] += ch - '0';
            }
        }
        return max_num[n][m] < 0? vector{0, 0} : vector{max_num[n][m], ways[n][m]};
    }
};