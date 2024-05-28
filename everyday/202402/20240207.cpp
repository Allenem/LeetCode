/*
2641. 二叉树的堂兄弟节点 II

给你一棵二叉树的根 root ，请你将每个节点的值替换成该节点的所有 堂兄弟节点值的和 。

如果两个节点在树中有相同的深度且它们的父节点不同，那么它们互为 堂兄弟 。

请你返回修改值之后，树的根 root 。

注意，一个节点的深度指的是从树根节点到这个节点经过的边数。

示例 1：

输入：root = [5,4,9,1,10,null,7]
输出：[0,0,0,7,7,null,11]
解释：上图展示了初始的二叉树和修改每个节点的值之后的二叉树。
- 值为 5 的节点没有堂兄弟，所以值修改为 0 。
- 值为 4 的节点没有堂兄弟，所以值修改为 0 。
- 值为 9 的节点没有堂兄弟，所以值修改为 0 。
- 值为 1 的节点有一个堂兄弟，值为 7 ，所以值修改为 7 。
- 值为 10 的节点有一个堂兄弟，值为 7 ，所以值修改为 7 。
- 值为 7 的节点有两个堂兄弟，值分别为 1 和 10 ，所以值修改为 11 。

示例 2：

输入：root = [3,1,2]
输出：[0,0,0]
解释：上图展示了初始的二叉树和修改每个节点的值之后的二叉树。
- 值为 3 的节点没有堂兄弟，所以值修改为 0 。
- 值为 1 的节点没有堂兄弟，所以值修改为 0 。
- 值为 2 的节点没有堂兄弟，所以值修改为 0 。

提示：

树中节点数目的范围是 [1, 105] 。
1 <= Node.val <= 104
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        root->val = 0;
        deque<TreeNode*> dq;
        dq.push_back(root);
        while (!dq.empty()) {
            int sum = 0, sz = dq.size();
            for (TreeNode* node : dq) {
                if (node->left != nullptr) sum += node->left->val;
                if (node->right != nullptr) sum += node->right->val;
            }
            while (sz-- > 0) {
                TreeNode* node = dq.front();
                dq.pop_front();
                int u = (node->left == nullptr ? 0 : node->left->val) + (node->right == nullptr ? 0 : node->right->val);
                if (node->left != nullptr) {
                    node->left->val = sum - u;
                    dq.push_back(node->left);
                }
                if (node->right != nullptr) {
                    node->right->val = sum - u;
                    dq.push_back(node->right);
                }
            }
        }
        return root;
    }
};

// Level Order Print
void printTreeNode(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
}

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(9);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(10);
    root->right->right = new TreeNode(7);
    TreeNode* result = solution.replaceValueInTree(root);
    printTreeNode(result);
    cout << endl;

    root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    result = solution.replaceValueInTree(root);
    printTreeNode(result);
    cout << endl;

    return 0;
}