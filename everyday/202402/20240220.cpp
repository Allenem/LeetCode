/*
105. 从前序与中序遍历序列构造二叉树

给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

示例 1:

输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]

示例 2:

输入: preorder = [-1], inorder = [-1]
输出: [-1]

提示:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder 和 inorder 均 无重复 元素
inorder 均出现在 preorder
preorder 保证 为二叉树的前序遍历序列
inorder 保证 为二叉树的中序遍历序列
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        unordered_map<int, int> d;
        for (int i = 0; i < n; ++i) d[inorder[i]] = i;
        // i, j, len 分别为前序序列的起始位置，中序序列的起始位置，节点个数
        function<TreeNode* (int, int, int)> dfs = [&](int i, int j, int len) -> TreeNode* {
            if (len <= 0) return nullptr;
            int v = preorder[i];
            int inIdx = d[v];
            TreeNode* l = dfs(i + 1, j, inIdx - j);
            TreeNode* r = dfs(i + 1 + inIdx - j, inIdx + 1, len - 1 - (inIdx - j));
            return new TreeNode(v, l, r);
            };
        return dfs(0, 0, n);
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
    vector<int> preorder = { 3,9,20,15,7 };
    vector<int> inorder = { 9,3,15,20,7 };
    Solution s;
    TreeNode* root = s.buildTree(preorder, inorder);
    printTree(root);

    preorder = { -1 };
    inorder = { -1 };
    root = s.buildTree(preorder, inorder);
    printTree(root);

    return 0;
}