/*
94. 二叉树的中序遍历

给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

示例 1：

输入：root = [1,null,2,3]
输出：[1,3,2]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100

进阶: 递归算法很简单，你可以通过迭代算法完成吗？
*/

#include <iostream>
#include <vector>
#include <functional>

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        function<void(TreeNode*)> inorder = [&](TreeNode* node) {
            if (!node) return;
            inorder(node->left);
            ret.push_back(node->val);
            inorder(node->right);
            };
        inorder(root);
        return ret;
    }
};

int main() {
    Solution s;

    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    vector<int> ret = s.inorderTraversal(root);
    for (int i : ret) {
        cout << i << " ";
    }
    cout << endl;

    TreeNode* root2 = nullptr;
    ret = s.inorderTraversal(root2);
    for (int i : ret) {
        cout << i << " ";
    }
    cout << endl;

    TreeNode* root3 = new TreeNode(1);
    ret = s.inorderTraversal(root3);
    for (int i : ret) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}