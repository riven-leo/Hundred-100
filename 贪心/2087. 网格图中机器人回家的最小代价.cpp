class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int ans = 0;
        // 等于的情况怎么处理
        if(startPos[0] < homePos[0]) {
            for(int r = startPos[0] + 1; r <= homePos[0]; r++) {
                ans += rowCosts[r];
            }
        }else {
            for(int r = startPos[0] - 1; r >= homePos[0]; r--) {
                ans += rowCosts[r];
            }
        }
        if(startPos[1] < homePos[1]) {
            for(int c = startPos[1] + 1; c <= homePos[1]; c++) {
                ans += colCosts[c];
            }
        }else {
            for(int c = startPos[1] - 1; c >= homePos[1]; c--) {
                ans += colCosts[c];
            }
        }
        return ans;
    }
};