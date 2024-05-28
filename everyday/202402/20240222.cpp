/*
889. 根据前序和后序遍历构造二叉树

给定两个整数数组，preorder 和 postorder ，其中 preorder 是一个具有 无重复 值的二叉树的前序遍历，postorder 是同一棵树的后序遍历，重构并返回二叉树。

如果存在多个答案，您可以返回其中 任何 一个。

示例 1：

输入：preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
输出：[1,2,3,4,5,6,7]

示例 2:

输入: preorder = [1], postorder = [1]
输出: [1]

提示：

1 <= preorder.length <= 30
1 <= preorder[i] <= preorder.length
preorder 中所有值都 不同
postorder.length == preorder.length
1 <= postorder[i] <= postorder.length
postorder 中所有值都 不同
保证 preorder 和 postorder 是同一棵二叉树的前序遍历和后序遍历
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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size();
        unordered_map<int, int> d;
        for (int i = 0; i < n; ++i) d[postorder[i]] = i;
        function<TreeNode* (int, int, int, int)> dfs = [&](int il, int ir, int jl, int jr) -> TreeNode* {
            if (ir < il) return nullptr;
            int v = preorder[il];
            int lcnt = 0;
            if (il < ir)
                lcnt = d[preorder[il + 1]] - jl + 1;
            TreeNode* l = dfs(il + 1, il + lcnt, jl, jl + lcnt - 1);
            TreeNode* r = dfs(il + lcnt + 1, ir, jl + lcnt, jr - 1);
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
    vector<int> preorder = { 1,2,4,5,3,6,7 }, postorder = { 4,5,2,6,7,3,1 };
    Solution s;
    TreeNode* root = s.constructFromPrePost(preorder, postorder);
    printTree(root);

    preorder = { 1 };
    postorder = { 1 };
    root = s.constructFromPrePost(preorder, postorder);
    printTree(root);

    return 0;
}