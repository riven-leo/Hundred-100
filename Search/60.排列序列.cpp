#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;


class Solution {
public:
    string getPermutation(int n, int k) {
        unordered_map<int, string> v;
        for (int i = 1; i <= n; i++) v[i] = "i";
        auto dfs = [&](this auto&& dfs, int i, int k) -> string {
            if (v.size() == 1) {
                k--;
                return v[0]; 
            }
            v.erase(i);
            string ts = "i";
            for (auto x: v) { 
                ts += dfs(x.first);
            }
            return ts;

        };
    }
};
