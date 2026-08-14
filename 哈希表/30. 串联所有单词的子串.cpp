#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        //特殊情况直接排除
        if(s.empty()||words.empty())return {};
        
        //存放结果的数组
        vector<int> result;
        
        //单词数组中的单词的大小，个数，以及总长度
        int one_word=words[0].size();
        int word_num=words.size();
        int all_len=one_word*word_num; // 当前实现未直接使用，总长度由 count 是否等于 word_num 判断。
        
        //建立单词->单词个数的映射
        unordered_map<string,int> m1;
        for(const auto& w:words)m1[w]++;
        
        // 按起点模 one_word 分组；每组都在完整单词边界上滑动。
        for(int i=0;i<one_word;++i)
        {
            //left和rigth表示窗口的左右边界，count用来统计匹配的单词个数
            int left=i,right=i,count=0;
            
            unordered_map<string,int>m2;
            
            //开始滑动窗口
            while(right+one_word<=s.size())
            {
                //从s中提取一个单词拷贝到w
                string w=s.substr(right,one_word);
                right+=one_word;//窗口右边界右移一个单词的长度
                
                if(m1.count(w)==0){//此单词不在words中，表示匹配不成功,然后重置单词个数、窗口边界、以及m2
                    count=0;
                    left=right;
                    m2.clear();
                }
                else{//该单词匹配成功，添加到m2中
                    m2[w]++;
                    count++;    
                    // 易错：可能超量多次，必须循环收缩，且同步更新频次与 count。
                    while(m2.at(w)>m1.at(w))
                    {
                        string t_w=s.substr(left,one_word);
                        count--;
                        m2[t_w]--;
                        left+=one_word;
                    }
                    if(count==word_num)result.push_back(left); // 此时窗口频次与目标频次完全一致。
                }
            }
        }
        return result;
    }
};
