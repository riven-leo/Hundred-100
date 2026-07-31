#include <algorithm>
#include <vector>
using namespace std;


class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        // start with 第一行的一个香槟杯
        vector<double> cur = {1.0 * poured};

        // 遍历每一行，获取下一行数组长度
        for (int i = 1; i <= query_row; i++) {
            // 建下一行数组
            vector<double> next(i + 1, 0.0);
            // 遍历当前行的所有香槟杯
            for (int j = 0; j < cur.size(); j++) {
                // if 当前酒>1, 溢出到下一行
                if (cur[j] > 1) {
                    next[j] += (cur[j] - 1) / 2;
                    next[j + 1] += (cur[j] - 1) / 2;
                }
            }
            cur = next;
        }
        // 可能存在大于1的情况，说明后面还会溢出
        return min(1.0, cur[query_glass]);
    }
};
