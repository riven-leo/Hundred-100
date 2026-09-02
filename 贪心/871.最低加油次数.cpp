#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 下面展示了学习的进步阶段
// 下一步√√√：优化变量名，使遍历名和含义对应上

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int curFuel = startFuel;
        // 当前消耗完油所在的位置
        int curpos = 0;
        int ans = 0;
        // 给加油站做标记，表示i前的加油站已经加入堆里
        int i = 0;
        // 优先队列维护每次取出的加油站油是最多的
        priority_queue<int> fuel_heap;
        
        while (true) {
            // 耗完所有的油,if已经到达target return
            curpos += curFuel;
            if (curpos >= target) return ans;

            // 把该位置前的所有没有加入堆的加油站都放入堆
            while (i < stations.size() && stations[i][0] <= curpos) {
                fuel_heap.push(stations[i][1]);
                i++;
            }

            // if 堆里没有加油站可以用了 return no solution
            if (fuel_heap.empty()) return -1;

            // 在油最多的加油站加一次油
            curFuel = fuel_heap.top();
            fuel_heap.pop();
            ans++;
        }
    }
};

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations){
        /*循环：
            用掉所有油
            如果到达终点则返回加油次数
            将经过的加油站放入heap中，按油量大小降序
            如果heap里没有油了返回-1
            使用油量最大的一站，加油次数+1
            # 用过的加油站pop out
            */
        priority_queue<int> h;
        int cnt = 0;
        int i = 0;
        while (true) {
            int cur = startFuel;
            if (cur >= target) return cnt;
            for (;i < stations.size() && stations[i][0] <= cur; i++) {
                h.push(stations[i][1]);
            }
            if (h.empty()) return -1;
            startFuel += h.top();
            h.pop();
            cnt++;
        }
    }
};