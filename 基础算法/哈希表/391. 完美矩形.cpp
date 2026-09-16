#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int n = rectangles.size();

        vector<vector<int>> rs(n * 2, vector<int>(4));

        // 把每个矩形拆成带方向的两条竖边，扫描时内部边界应成对抵消。
        for (int i = 0, idx = 0; i < n; i++) {
            auto& re = rectangles[i];

            rs[idx++] = {re[0], re[1], re[3], 1};   // 左边竖线
            rs[idx++] = {re[2], re[1], re[3], -1};  // 右边竖线
        }

        sort(rs.begin(), rs.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] != b[0])
                return a[0] < b[0];
            return a[1] < b[1];
        });

        n *= 2;

        // 存储同一个x坐标下左右两侧的线段
        vector<vector<int>> l1, l2;

        for (int l = 0; l < n;) {
            int r = l;

            l1.clear();
            l2.clear();

            // 找到相同横坐标的一组竖边
            while (r < n && rs[r][0] == rs[l][0])
                r++;

            for (int i = l; i < r; i++) {
                vector<int> cur = {rs[i][1], rs[i][2]};

                vector<vector<int>>& list = 
                    (rs[i][3] == 1 ? l1 : l2);

                if (list.empty()) {
                    list.push_back(cur);
                } 
                else {
                    vector<int>& prev = list.back();

                    if (cur[0] < prev[1]) {
                        // 易错：同侧线段重叠意味着矩形发生重叠，不能当作普通合并。
                        return false;
                    }
                    else if (cur[0] == prev[1]) {
                        // 首尾相接，合并
                        prev[1] = cur[1];
                    }
                    else {
                        list.push_back(cur);
                    }
                }
            }

            if (l > 0 && r < n) {
                // 中间的竖边，左右必须逐段完全匹配；只比较总长度会漏掉空洞。
                if (l1.size() != l2.size())
                    return false;

                for (int i = 0; i < l1.size(); i++) {
                    if (l1[i][0] == l2[i][0] &&
                        l1[i][1] == l2[i][1])
                        continue;

                    return false;
                }
            }
            else {
                // 最左边或最右边是外轮廓，只能形成一条连续完整边。
                if (l1.size() + l2.size() != 1)
                    return false;
            }

            l = r;
        }

        return true;
    }
};
