/*
103. 二叉树的锯齿形层序遍历

给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：[[3],[20,9],[15,7]]

示例 2：

输入：root = [1]
输出：[[1]]

示例 3：

输入：root = []
输出：[]

提示：

树中节点数目在范围 [0, 2000] 内
-100 <= Node.val <= 100
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        deque<TreeNode*> dq;
        dq.push_back(root);
        bool flag = true;
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
            if (!flag)reverse(tmp.begin(), tmp.end());
            ret.push_back(tmp);
            flag = !flag;
        }
        return ret;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    vector<vector<int>> ans = s.zigzagLevelOrder(root);
    for (const auto& col : ans) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    root = new TreeNode(1);
    ans = s.zigzagLevelOrder(root);
    for (const auto& col : ans) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    root = nullptr;
    ans = s.zigzagLevelOrder(root);
    for (const auto& col : ans) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}