/*
102. 二叉树的层序遍历

给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]

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
#include <deque>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        deque<TreeNode*> dq;
        dq.push_back(root);
        while (!dq.empty()) {
            vector<int> tmp;
            int sz = dq.size();
            for (int i = 0;i < sz;++i) {
                TreeNode* node = dq.front();
                dq.pop_front();
                tmp.push_back(node->val);
                if (node->left)
                    dq.push_back(node->left);
                if (node->right)
                    dq.push_back(node->right);
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    vector<vector<int>> res = s.levelOrder(root);
    for (auto& r : res) {
        for (auto& i : r)
            cout << i << ' ';
        cout << endl;
    }
    cout << endl;

    TreeNode* root2 = new TreeNode(1);
    vector<vector<int>> res2 = s.levelOrder(root2);
    for (auto& r : res2) {
        for (auto& i : r)
            cout << i << ' ';
        cout << endl;
    }
    cout << endl;

    TreeNode* root3 = nullptr;
    vector<vector<int>> res3 = s.levelOrder(root3);
    for (auto& r : res3) {
        for (auto& i : r)
            cout << i << ' ';
        cout << endl;
    }
    cout << endl;

    return 0;
}

