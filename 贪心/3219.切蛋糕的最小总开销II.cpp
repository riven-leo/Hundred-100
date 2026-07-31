#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        long long ans = 0; 
        // 水平需要切的刀数，垂直需要切的刀数
        long long h = 1, v = 1;
        // 升序切的cost，为贪心做准备
        sort(horizontalCut.begin(), horizontalCut.end());
        sort(verticalCut.begin(), verticalCut.end());
        // 开始贪心切
        /* Repeat：
            if 两个数组都遍历完了就 return ans
            if 垂直的刀切完了 or 水平的刀还没切完 and 水平刀最大的cost > 垂直刀最大的cost，水平切一刀：
                ans += 水平cost*h, 删除该刀, 垂直需要切的刀数+1
            else 垂直切一刀*/
        while (!horizontalCut.empty() || !verticalCut.empty()) {
            if (verticalCut.empty() || !horizontalCut.empty() && horizontalCut.back() > verticalCut.back()) {
                ans += horizontalCut.back()*h;
                horizontalCut.pop_back();
                v++;
            }
            else {
                ans += verticalCut.back()*v;
                verticalCut.pop_back();
                h++;
            }
        }
        return ans;
    }
};