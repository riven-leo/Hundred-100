class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        /*Datastru：因为杨辉三角，下一行比前一行多一个
        第一行放所有的酒
        Δ循环目的：建立从1行到query_row行
            创建下一行
            遍历当前行将多出来的酒向下一行溢    
            将下一行更新为当前行
        return min(1.0, cur[query_glass])*/
        vector<double> cur = {1.0 * poured};

        // 第0行已经建立，所以循环变量i从第1行开始
        for (int j = 1; j <= query_row; j++) {
            vector<double> next(j+1, 0.0); 
            for (int i = 0; i < cur.size(); i++) {
                if (cur[i] > 1.0) {
                    next[i] += (cur[i]-1) / 2;
                    next[i+1] += (cur[i]-1) / 2;
                }
            }
            cur = next;
        }
        return min(1.0, cur[query_glass]);
    }
};