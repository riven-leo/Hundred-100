// √看懂答案 √√理解思想、能分析复杂度、看到题能写出伪代码 √√√能实现C++代码

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
        /*两个递归出口是和"分"密切相关的*/
        // 只剩一个链表
        if (l == r) return lists[l];

        // 为了处理特殊情况，当给的lists是空的时候，l=0,r=-1
        if (l > r) return nullptr;

        /*分：[l,mid], [mid+1,r]
          治：递归把左边若干链表合并成一个，把右边若干链表合并成一个
          合：调用 mergeTwolist() 把这两个结果再合并*/
        int mid = (l + r) >> 1; 
        // 奇数取中间，偶数取平分后左边最后一个
        // c++/2操作向0取整, (0,4)mid=2这有5个数,2是第3个数, (0,5)mid=2这有6个数
        return mergeTwolist(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};
