#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


struct Node {
    Node *son[26]{};
    int cnt = 0; // 此前恰好在当前节点结束的单词数，不是经过次数。
};

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string> &words) {
        long long ans = 0;
        Node *root = new Node();
        for (string &t: words) {
            int n = t.length();
            // Z[i] = t 与后缀 t[i..] 的最长公共前缀长度。
            vector<int> z(n);
            int l = 0, r = 0;
            for (int i = 1; i < n; i++) {
                if (i <= r) {
                    z[i] = min(z[i - l], r - i + 1);
                }
                while (i + z[i] < n && t[z[i]] == t[i + z[i]]) {
                    l = i;
                    r = i + z[i];
                    z[i]++;
                }
            }
            z[0] = n;

            auto cur = root;
            for (int i = 0; i < n; i++) {
                int c = t[i] - 'a';
                if (cur->son[c] == nullptr) {
                    cur->son[c] = new Node();
                }
                cur = cur->son[c];
                if (z[n - 1 - i] == i + 1) { // 长为 i+1 的前缀同时也是后缀。
                    ans += cur->cnt;
                }
            }
            // 易错：统计完成后再登记当前单词，才能保证配对下标严格满足 earlier < current。
            cur->cnt++;
        }
        return ans;
    }
};
