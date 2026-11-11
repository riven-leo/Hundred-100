#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class Solution {
    // 计算 s 和 t 的最长公共前缀（LCP）长度
    int calc_lcp(string& s, string& t) {
        int len = min(s.size(), t.size());
        for (int i = 0; i < len; i++) {
            if (s[i] != t[i]) {
                return i;
            }
        }
        return len;
    }

public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size();
        if (k >= n) { // 移除一个字符串后，剩余字符串少于 k 个
            return vector<int>(n);
        }

        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        // 保留原下标，只对 idx 排序；最终答案才能写回被删除字符串的原位置。
        ranges::sort(idx, {}, [&](int i) -> auto& { return words[i]; }); // 注意要返回引用，不然会 copy

        // 相同前缀在字典序中连续；k 个字符串的 LCP 等于排序窗口两端的 LCP。
        // 同时保留最大和次大候选，以处理删除元素破坏最优窗口的情况。
        int mx = -1, mx2 = -1, mx_i = -1;
        for (int i = 0; i <= n - k; i++) {
            // 排序后，[i, i+k-1] 的 LCP 等于两端点的 LCP
            int lcp = calc_lcp(words[idx[i]], words[idx[i + k - 1]]);
            if (lcp > mx) {
                mx2 = mx;
                mx = lcp;
                mx_i = i;
            } else if (lcp > mx2) {
                mx2 = lcp;
            }
        }

        vector<int> ans(n, mx); // 先初始化成最大 LCP 长度
        // 只有删除最优窗口内的字符串才会破坏该窗口，此时退回次大候选。
        for (int i : ranges::subrange(idx.begin() + mx_i, idx.begin() + mx_i + k)) {
            ans[i] = mx2; // 改成次大 LCP 长度
        }
        return ans;
    }
};
