#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> factorial(n + 1);
        factorial[0] = 1;

        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        vector<bool> used(n + 1, false);
        string path;

        auto dfs = [&](this auto&& dfs, int index, int k) -> void {
            if (index == n) {
                return;
            }

            // 当前选择一个数字后，剩余数字的全排列数量
            int count = factorial[n - 1 - index];

            for (int i = 1; i <= n; i++) {
                if (used[i]) {
                    continue;
                }

                // 第 k 个排列不在这一组，直接跳过整组
                if (count < k) {
                    k -= count;
                    continue;
                }

                path += to_string(i);
                used[i] = true;

                dfs(index + 1, k);
                return;
            }
        };

        dfs(0, k);

        return path;
    }
};
