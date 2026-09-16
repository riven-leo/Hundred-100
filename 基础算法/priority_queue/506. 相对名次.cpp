#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        string medal[3] = {"Gold Medal", "Silver Medal", "Bronze Medal"} ;
        vector<pair<int, int>> m;
        
        for (int i = 0; i < score.size(); i++) {
            // 将得分变成负数存入，再sort，得到的就是绝对值最大的在开头，能达到降序的效果
            m.emplace_back(-score[i], i); 
            // O(1)
        }
        // O(n)

        sort(m.begin(), m.end());  
        // O(nlogn)

        vector<string> ans(score.size());
        for (int i = 0; i < m.size(); i++) {
            if (i < 3) ans[m[i].second] = medal[i];
            else ans[m[i].second] = to_string(i+1); 
            // to_string O(b)逐位变成字符
        } 
        // O(n)

        return ans;
    }
};