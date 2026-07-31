#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        int ans = 1;
        vector<vector<int>> g(n);
        
        for (int i = 0; i < n; i++) {
            long long xi = bombs[i][0];
            long long yi = bombs[i][1];
            long long zi = bombs[i][2];
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                long long xj = bombs[j][0];
                long long yj = bombs[j][1];
                if (zi*zi >= (xi-xj)*(xi-xj) + (yi-yj)*(yi-yj)){
                    g[i].push_back(j);
                }
            }
        }
        
        for (int i = 0; i < n; i ++) {
            vector<int> vis(n,0);
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            int cnt = 0;//1
            while (!q.empty()) {
                int one = q.front();
                q.pop();
                cnt++;
                // vis[one] = 1;
                for (int x: g[one]) {
                    if (vis[x] != 1) {
                        q.push(x);
                        vis[x] = 1;
                    }
                }
            }
            ans = max(ans, cnt);
        }

        for (int i = 0; i < n; i ++) {
            vector<int> vis(n,0);
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            int cnt = 1;
            while (!q.empty()) {
                int one = q.front();
                q.pop();
                for (int x: g[one]) {
                    if (vis[x] != 1) {
                        q.push(x);
                        vis[x] = 1;
                        cnt++;
                    }
                }
            }
            ans = max(ans, cnt);
        }
        
        return ans;
    }
};

