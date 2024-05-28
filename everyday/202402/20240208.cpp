/*
993. 二叉树的堂兄弟节点

在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。

如果二叉树的两个节点深度相同，但 父节点不同 ，则它们是一对堂兄弟节点。

我们给出了具有唯一值的二叉树的根节点 root ，以及树中两个不同节点的值 x 和 y 。

只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true 。否则，返回 false。

示例 1：

输入：root = [1,2,3,4], x = 4, y = 3
输出：false

示例 2：

输入：root = [1,2,3,null,4,null,5], x = 5, y = 4
输出：true

示例 3：

输入：root = [1,2,3,null,4], x = 2, y = 3
输出：false

提示：

二叉树的节点数介于 2 到 100 之间。
每个节点的值都是唯一的、范围为 1 到 100 的整数。
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
    bool isCousins(TreeNode* root, int x, int y) {
        int parentx, parenty, depx, depy;
        function<void(TreeNode*, int, int, int, int)> dfs = [&](TreeNode* nxt, int curval, int dep, int x, int y) {
            if (nxt == nullptr) return;
            if (nxt->val == x) {
                parentx = curval;
                depx = dep;
            }
            else if (nxt->val == y) {
                parenty = curval;
                depy = dep;
            }
            dfs(nxt->left, nxt->val, dep + 1, x, y);
            dfs(nxt->right, nxt->val, dep + 1, x, y);
            };
        dfs(root->left, root->val, 1, x, y);
        dfs(root->right, root->val, 1, x, y);
        return (depx == depy) && (parentx != parenty);
    }
};

int main() {
    Solution sol;

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    cout << sol.isCousins(root, 4, 3) << endl;

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->right = new TreeNode(4);
    root2->right->right = new TreeNode(5);
    cout << sol.isCousins(root2, 5, 4) << endl;

    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(3);
    root3->left->right = new TreeNode(4);
    cout << sol.isCousins(root3, 2, 3) << endl;

    return 0;
}