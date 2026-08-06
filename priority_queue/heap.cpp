#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Maxheap {
    vector<int> h;

    int left(int i) {
        return 2*i+1;
    }

    int right(int i) {
        return 2*i+2;
    }

    int parent(int i) {
        return (i-1)/2;
    }

    int top() {
        if (!h.empty())
            return h[0];
    }

    void heapifyup(int i) {
        // 只有索引大于0时才会调用parent(i)
        while (i > 0) { 
            int p = parent(i);
            // if写错误退出逻辑更好，ai课英文搜索伪代码也这么写
            if (h[i] <= h[p]) break; // Minheap >=
            swap(h[i], h[p]);
            i = p;
        }
    }
    // O(n)

    void heapifydown(int i) {
        // 左子存在才可能有右子存在
        while (left(i) < h.size()) {
            // 假设左子值为最大值
            int ma = left(i); // mi
            // 右子存在 并且 右子值大于左子值 更新最大值为右子值
            if (right(i) < h.size() && h[right(i)] > h[left(i)]) // Minheap <
                ma = right(i); 
            // 当前值大于等于最大值，建堆完成
            if (h[i] >= h[ma]) break; // Minheap <= 
            swap(h[i], h[ma]);
            i = ma;
        }
    }
    // O(n)

    void push(int val) {
        h.push_back(val);
        // 从最后位置开始向上堆化
        heapifyup(h.size()-1);
    }
    // O(logn)

    void pop() {
        if (h.empty()) return;
        h[0] = h.back();
        h.pop_back();
        // 从0位置开始向下堆化
        heapifydown(0);
    }
    // O(logn)
};