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
        // 提前存可以用到的东西，1到9的阶乘数
        vector<int> factorial(n + 1);
        factorial[0] = 1;
        for (int i = 1; i <= n; i++) {
            factorial[i] = factorial[i - 1] * i;
        }

        vector<bool> used(n + 1, false);
        string path;

        // index当前在选哪一个位置
        auto dfs = [&](this auto&& dfs, int index, int k) -> void {
            if (index == n) {
                return;
            }

            // 当前选择一个数字后，剩余数字的全排列数量
            int count = factorial[n - 1 - index];

            // for循环遍历所有数，保证不重复使用可以用的数
            // 比如刚用过了4，因为是遍历，就算撤销了4的使用，也不会再重复用一次4
            for (int i = 1; i <= n; i++) {
                if (used[i]) {
                    continue;
                }

                // 发现第 k 个排列不在这一组，直接跳过整组，该位置换一个数字，继续累加全排列数量
                if (count < k) {
                    k -= count;
                    continue;
                }// 剪枝

                // 做选择
                path += to_string(i);
                used[i] = true;

                // 这里的k就是为了放进每次dfs里用于剪枝的
                dfs(index + 1, k);

                // 这里比较独特不需要撤回操作
                return;
            }
        };

        dfs(0, k);

        return path;
    }
};


// 原始回溯代码
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<bool> used(n + 1, false);
        string path;
        string ans;
        int cnt = 0;

        auto dfs = [&](this auto&& dfs, int index) -> void {
            if (index == n) {
                cnt++;

                if (cnt == k) {
                    ans = path;
                }

                return;
            }

            for (int i = 1; i <= n; i++) {
                if (used[i]) {
                    continue;
                }

                path += to_string(i);
                used[i] = true;

                dfs(index + 1);

                used[i] = false;
                path.pop_back();
            }
        };

        dfs(0);

        return ans;
    }
};