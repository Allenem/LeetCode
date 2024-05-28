/*
106. 从中序与后序遍历序列构造二叉树

给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

示例 1:

输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]

示例 2:

输入：inorder = [-1], postorder = [-1]
输出：[-1]

提示:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder 和 postorder 都由 不同 的值组成
postorder 中每一个值都在 inorder 中
inorder 保证是树的中序遍历
postorder 保证是树的后序遍历
*/

#include <iostream>
#include <vector>
#include <functional>
#include <queue>

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();
        unordered_map<int, int> d;
        for (int i = 0; i < n; ++i) d[inorder[i]] = i;
        function<TreeNode* (int, int, int, int)> dfs = [&](int il, int ir, int pl, int pr) -> TreeNode* {
            if (ir < il) return nullptr;
            int v = postorder[pr];
            int inIdx = d[v];
            TreeNode* l = dfs(il, inIdx - 1, pl, pl + inIdx - 1 - il);
            TreeNode* r = dfs(inIdx + 1, ir, pl + inIdx - 1 - il + 1, pr - 1);
            return new TreeNode(v, l, r);
            };
        return dfs(0, n - 1, 0, n - 1);
    }
};

// print TreeNode in level order
void printTree(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node) {
            cout << node->val << " ";
            q.push(node->left);
            q.push(node->right);
        }
        else {
            cout << "null ";
        }
    }
    cout << endl;
}

int main() {
    vector<int> inorder = { 9,3,15,20,7 }, postorder = { 9,15,7,20,3 };
    Solution s;
    TreeNode* root = s.buildTree(inorder, postorder);
    printTree(root);

    inorder = { -1 };
    postorder = { -1 };
    root = s.buildTree(inorder, postorder);
    printTree(root);

    return 0;
}