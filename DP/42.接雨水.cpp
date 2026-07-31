#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int n = height.size();
        for (int i = 1; i < n - 1; i++) {
            int lmax = 0, rmax = 0;

            // 算左边最高
            for (int i = i - 1; i >= 0; i--)
                lmax = max(lmax, height[i]);

            // 算右边最高
            for (int i = i + 1; i <= height.size() - 1; i++)
                rmax = max(rmax, height[i]);

            // 计算雨水
            if (min(lmax, rmax) > height[i])
                ans += min(lmax, rmax) - height[i];
        }
        return ans;
    }
};

// DP优化
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int n = height.size();

        // 存左右最高
        vector<int> lmax(n), rmax(n);
        lmax[0] = height[0], rmax[n - 1] = height[n - 1];

        // 预处理左右最高
        for (int i = 1; i < n; i++)
            lmax[i] = max(lmax[i - 1], height[i - 1]);
        for (int i = n - 2; i >= 0; i--)
            rmax[i] = max(rmax[i + 1], height[i + 1]);

        // 遍历每一列计算雨水
        for (int i = 1; i < n - 1; i++) {
            if (min(lmax[i], rmax[i]) > height[i])
                ans += min(lmax[i], rmax[i]) - height[i];
        }
        return ans;
    }
};