/*
107. 二叉树的层序遍历 II

给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：[[15,7],[9,20],[3]]

示例 2：

输入：root = [1]
输出：[[1]]

示例 3：

输入：root = []
输出：[]

提示：

树中节点数目在范围 [0, 2000] 内
-1000 <= Node.val <= 1000
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ret;
        if (!root) return ret;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            int n = q.size();
            ret.push_back(vector<int>());
            for (int i = 0;i < n;++i)
            {
                TreeNode* tmp = q.front();
                q.pop();
                ret.back().push_back(tmp->val);
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    vector<vector<int>> res = s.levelOrderBottom(root);
    for (auto& r : res)
    {
        for (auto& c : r)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;

    TreeNode* root2 = new TreeNode(1);
    vector<vector<int>> res2 = s.levelOrderBottom(root2);
    for (auto& r : res2)
    {
        for (auto& c : r)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;

    TreeNode* root3 = nullptr;
    vector<vector<int>> res3 = s.levelOrderBottom(root3);
    for (auto& r : res3)
    {
        for (auto& c : r)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}