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
        while (!horizontalCut.empty() || !verticalCut.empty()) {
            if (verticalCut.empty() || !horizontalCut.empty() && horizontalCut.back() > verticalCut.back()) {

                // 取水平最大的一刀cost*当前水平需要切的刀数
                ans += horizontalCut.back()*h;
                horizontalCut.pop_back();
                // 垂直需要切的刀数+1
                v++;
            }
            else {

                // 取垂直最大的一刀cost*当前垂直需要切的刀数
                ans += verticalCut.back()*v;
                verticalCut.pop_back();
                // 水平需要切的刀数+1
                h++;
            }
        }
        return ans;
    }
};