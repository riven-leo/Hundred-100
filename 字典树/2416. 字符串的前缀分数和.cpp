#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> sumPrefixScores(vector<string> &words) {
        struct Node {
            Node *son[26]{};
            int score = 0; // 经过当前前缀节点的字符串数量，不是单词结束数量。
        };
        Node *root = new Node();
        for (auto &word : words) {
            auto cur = root;
            for (char c : word) {
                c -= 'a';
                if (cur->son[c] == nullptr) cur->son[c] = new Node();
                cur = cur->son[c];
                ++cur->score; // 易错：先进入字符节点，再更新这个非空前缀的分数。
            }
        }

        int n = words.size();
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            auto cur = root;
            for (char c : words[i]) {
                // 所有单词已建树，路径必然存在；沿途分数之和就是该单词答案。
                cur = cur->son[c - 'a'];
                ans[i] += cur->score; // 累加分数，即可得到答案
            }
        }
        return ans;
    }
};
