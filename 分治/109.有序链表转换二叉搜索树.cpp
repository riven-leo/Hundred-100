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
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    TreeNode* build(vector<int>& v, int l, int r) {
        // 易错，递归出口
        if (l > r) return nullptr;
        
        // 数组中点
        int mid = l + r >> 1;

        // 构建子树
        TreeNode* root = new TreeNode(v[mid]);
        root->left = build(v, l, mid-1);
        root->right = build(v, mid+1, r);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        // 链表先转换成数组，方便取中点
        vector<int> v;
        while(head != nullptr) {
            v.push_back(head->val);
            head = head->next;
        }

        return build(v, 0, v.size()-1);
    }
};

class Solution {
public:
    // 快慢指针取链表中点
    ListNode* getMid(ListNode* head, ListNode* end) {
        ListNode* slow = head;
        ListNode* fast = head;

        // 当fast指针到链表尾部的时候，slow指针恰好在链表中点
        while(fast != end && fast->next != end) {
            slow = slow->next;
            fast = fast->next->next;  
        }
        return slow;
    }
    // 构建子树
    TreeNode* build(ListNode* head, ListNode* end) {
        // 易错，递归出口
        if (head == end) return nullptr;
        
        ListNode* mid = getMid(head, end);

        // 构建子树
        TreeNode* root = new TreeNode(mid->val);
        root->left = build(head, mid);
        root->right = build(mid->next, end);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        return build(head, nullptr);
    }
};
