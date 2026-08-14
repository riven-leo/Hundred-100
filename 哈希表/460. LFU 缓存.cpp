#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
using namespace std;


// 为方便读者理解核心逻辑，该写法没有删除空的 list
struct Entry {
    int key, value, freq; // freq 表示这本书被看的次数
};

class LFUCache {
private:
    int capacity;
    int min_freq;
    unordered_map<int, list<Entry>::iterator> key_to_iter;
    unordered_map<int, list<Entry>> freq_to_list;

    void move(list<Entry>::iterator it) {
        // 必须先复制：erase 后原迭代器立即失效。
        Entry e = *it;
        freq_to_list[e.freq].erase(it); // 把这本书抽出来
        if (freq_to_list[min_freq].empty()) { // 最左边那摞书是空的
            min_freq++;
        }
        e.freq++; // 看书次数 +1
        // 同频率内按 LRU 排序：链表头最新，链表尾最旧。
        freq_to_list[e.freq].emplace_front(e); // 放在右边这摞书的最上面
        key_to_iter[e.key] = freq_to_list[e.freq].begin(); // 记录位置，这样可以 O(1) 从 list 中删除（把书抽出来）
    }

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = key_to_iter.find(key);
        if (it == key_to_iter.end()) { // 没有这本书
            return -1;
        }
        int value = it->second->value;
        move(it->second);
        return value;
    }

    void put(int key, int value) {
        // 易错：若题目允许 capacity==0，这里应先直接 return，避免从空链表淘汰。
        auto it = key_to_iter.find(key);
        if (it != key_to_iter.end()) { // 有这本书
            it->second->value = value; // 更新 value
            move(it->second);
            return;
        }
        if (key_to_iter.size() == capacity) { // 书太多了
            // 淘汰最低频率桶中最久未使用的节点，并同步删除 key 映射。
            auto& lst = freq_to_list[min_freq];
            key_to_iter.erase(lst.back().key);
            lst.pop_back();
        }
        freq_to_list[1].emplace_front(key, value, 1); // 把新书放在「看过 1 次」的最上面
        key_to_iter[key] = freq_to_list[1].begin();
        min_freq = 1; // 新节点出现后，全局最低频率必定重置为 1。
    }
};
