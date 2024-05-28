/*
938. 二叉搜索树的范围和

给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。

示例 1：

输入：root = [10,5,15,3,7,null,18], low = 7, high = 15
输出：32

示例 2：

输入：root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
输出：23

提示：

树中节点数目在范围 [1, 2 * 104] 内
1 <= Node.val <= 105
1 <= low <= high <= 105
所有 Node.val 互不相同
*/
#include <iostream>
#include <vector>
#include <queue>
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
    int rangeSumBST(TreeNode* root, int low, int high) {
        int ans = 0;
        function<void(TreeNode*)> dfs = [&](TreeNode* node) {
            if (node == nullptr)return;
            if (node->val >= low && node->val <= high) {
                ans += node->val;
                dfs(node->left);
                dfs(node->right);
            }
            else if (node->val < low) dfs(node->right);
            else dfs(node->left);
            };
        dfs(root);
        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(18);
    Solution s;
    cout << s.rangeSumBST(root, 7, 15) << endl;

    TreeNode* root2 = new TreeNode(10);
    root2->left = new TreeNode(5);
    root2->right = new TreeNode(15);
    root2->left->left = new TreeNode(3);
    root2->left->right = new TreeNode(7);
    root2->right->left = new TreeNode(13);
    root2->right->right = new TreeNode(18);
    root2->left->left->left = new TreeNode(1);
    root2->left->right->left = new TreeNode(6);
    cout << s.rangeSumBST(root2, 6, 10) << endl;

    return 0;
}