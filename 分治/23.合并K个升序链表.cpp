#include <algorithm>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    // 合并两个链表模板
    ListNode* mergeTwolist(ListNode* l1, ListNode* l2) {
        // 哨兵指针
        ListNode* pre = new ListNode(-1);

        // 当前节点的指针
        ListNode* cur = pre;

        // Repeat ： if 两个链表有一个空了 return solution
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }

        // 把另一个剩下没空的加在cur后面
        cur->next = l1 ? l1 : l2;

        // 哨兵指针后面的指针 = 合并后的链表的开头
        return pre->next;
    }

    
    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        // 只剩一个链表
        if (l == r) return lists[l];

        // 为了处理特殊情况，当给的lists是空的时候，l=0,r=-1
        if (l > r) return nullptr;

        int mid = (l + r) >> 1;
        return mergeTwolist(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};
