/*
145. 二叉树的后序遍历

给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。

示例 1：

输入：root = [1,null,2,3]
输出：[3,2,1]

示例 2：

输入：root = []
输出：[]

示例 3：

输入：root = [1]
输出：[1]

提示：

树中节点的数目在范围 [0, 100] 内
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        function<void(TreeNode*)> postorder = [&](TreeNode* node) {
            if (!node) return;
            postorder(node->left);
            postorder(node->right);
            ret.push_back(node->val);
            };
        postorder(root);
        return ret;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    vector<int> ret = s.postorderTraversal(root);
    for (int i : ret) {
        cout << i << " ";
    }
    cout << endl;

    TreeNode* root2 = nullptr;
    vector<int> ret2 = s.postorderTraversal(root2);
    for (int i : ret2) {
        cout << i << " ";
    }
    cout << endl;

    TreeNode* root3 = new TreeNode(1);
    vector<int> ret3 = s.postorderTraversal(root3);
    for (int i : ret3) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}