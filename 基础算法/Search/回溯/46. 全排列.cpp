class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        
        /*void DFS选择每个位置：
            选完所有位置，将结果存入ans后退出
            循环每个数
                用过跳过
                选择
                进入下一个位置
                撤回选择另一个
        从0开始DFS*/
        int n = nums.size();
        unordered_map<int, int8_t> used;
        for(int i: nums) used[i] = 0;

        vector<vector<int>> ans;
        vector<int> path; 
        auto dfs = [&](this auto&& dfs, int index) -> void {
            if (index == n) {
                ans.push_back(path);
                return;
            }
            for (int i: nums) {
                
                if (used[i]) continue;
                
                path.push_back(i);
                used[i] = 1;

                dfs(index+1);
                
                path.pop_back();
                used[i] = 0;
            }
        };
        dfs(0);
        return ans;
    }
};