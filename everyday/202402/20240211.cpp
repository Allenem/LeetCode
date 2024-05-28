/*
144. 二叉树的前序遍历

给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

示例 1：

输入：root = [1,null,2,3]
输出：[1,2,3]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

示例 4：

输入：root = [1,2]
输出：[1,2]

示例 5：

输入：root = [1,null,2]
输出：[1,2]

提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100

进阶：递归算法很简单，你可以通过迭代算法完成吗？
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        function<void(TreeNode*)> preorder = [&](TreeNode* node) {
            if (!node) return;
            ret.push_back(node->val);
            preorder(node->left);
            preorder(node->right);
            };
        preorder(root);
        return ret;
    }
};

int main() {
    Solution s;

    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    vector<int> ret = s.preorderTraversal(root);
    for (int i : ret) cout << i << " ";
    cout << endl;

    TreeNode* root2 = nullptr;
    vector<int> ret2 = s.preorderTraversal(root2);
    for (int i : ret2) cout << i << " ";
    cout << endl;

    TreeNode* root3 = new TreeNode(1);
    vector<int> ret3 = s.preorderTraversal(root3);
    for (int i : ret3) cout << i << " ";
    cout << endl;

    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    vector<int> ret4 = s.preorderTraversal(root4);
    for (int i : ret4) cout << i << " ";
    cout << endl;

    TreeNode* root5 = new TreeNode(1);
    root5->right = new TreeNode(2);
    vector<int> ret5 = s.preorderTraversal(root5);
    for (int i : ret5) cout << i << " ";
    cout << endl;

    return 0;
}