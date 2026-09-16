#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), ans = 0;
        for (int i = 0; i < n - 1; i++) { // 假设直线一定经过 points[i]
            auto& p = points[i];
            // 每换一个基准点都要重新分组：key 是从 p 出发的方向。
            unordered_map<double, int> cnt;
            for (int j = i + 1; j < n; j++) {
                auto& q = points[j];
                int dx = q[0] - p[0], dy = q[1] - p[1];
                // 竖线统一为无穷；易错：double 作键有精度风险，稳健写法应以 gcd 约分整数方向。
                double k = dx ? 1.0 * dy / dx : numeric_limits<double>::infinity();
                ans = max(ans, ++cnt[k]); // 这里没有算上 p 这个点，最后再加一
            }
        }
        return ans + 1;
    }
};
