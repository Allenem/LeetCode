/*
1026. 节点与其祖先之间的最大差值

给定二叉树的根节点 root，找出存在于 不同 节点 A 和 B 之间的最大值 V，其中 V =
|A.val - B.val|，且 A 是 B 的祖先。

（如果 A 的任何子节点之一为 B，或者 A 的任何子节点是 B 的祖先，那么我们认为 A 是
B 的祖先）

示例 1：

输入：root = [8,3,10,1,6,null,14,null,null,4,7,13]
输出：7
解释：
我们有大量的节点与其祖先的差值，其中一些如下：
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
在所有可能的差值中，最大值 7 由 |8 - 1| = 7 得出。

示例 2：

输入：root = [1,null,2,null,0,3]
输出：3

提示：

树中的节点数在 2 到 5000 之间。
0 <= Node.val <= 10^5
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    int maxAncestorDiff(TreeNode* root) {
        stack<TreeNode*> st;
        stack<long> stm;  // 存放祖先节点的最大值(高16位) 最小值(低16位)
        st.push(root);
        stm.push((long)((root->val << 16) + root->val));
        int ans = 0;
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            int mn = stm.top() & 0xffff, mx = stm.top() >> 16;
            stm.pop();
            ans = max(ans, abs(node->val - mn));
            ans = max(ans, abs(node->val - mx));
            if (node->left) {
                st.push(node->left);
                stm.push((long)(max(node->left->val, mx) << 16) +
                         min(node->left->val, mn));
            }
            if (node->right) {
                st.push(node->right);
                stm.push((long)(max(node->right->val, mx) << 16) +
                         min(node->right->val, mn));
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    TreeNode* root = new TreeNode(
        8,
        new TreeNode(3, new TreeNode(1),
                     new TreeNode(6, new TreeNode(4), new TreeNode(7))),
        new TreeNode(10, nullptr, new TreeNode(14, new TreeNode(13), nullptr)));
    cout << sol.maxAncestorDiff(root) << endl;

    root = new TreeNode(
        1, nullptr,
        new TreeNode(2, nullptr, new TreeNode(0, new TreeNode(3), nullptr)));
    cout << sol.maxAncestorDiff(root) << endl;
    return 0;
}