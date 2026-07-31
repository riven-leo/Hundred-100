#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

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
