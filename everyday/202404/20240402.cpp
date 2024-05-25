/*
894. 所有可能的真二叉树

给你一个整数 n ，请你找出所有可能含 n 个节点的 真二叉树
，并以列表形式返回。答案中每棵树的每个节点都必须符合 Node.val == 0 。

答案的每个元素都是一棵真二叉树的根节点。你可以按 任意顺序
返回最终的真二叉树列表。

真二叉树 是一类二叉树，树中每个节点恰好有 0 或 2 个子节点。

示例 1：

输入：n = 7
输出：[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

示例 2：

输入：n = 3
输出：[[0,0,0]]

提示：

1 <= n <= 20
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> res;
        if (n % 2 == 0)
            return res;
        if (n == 1) {
            TreeNode* node = new TreeNode(0);
            res.push_back(node);
        } else {
            for (int i = 1; i <= n - 2; i += 2) {
                for (auto l : allPossibleFBT(i)) {
                    for (auto r : allPossibleFBT(n - 1 - i)) {
                        TreeNode* node = new TreeNode(0);
                        node->left = l;
                        node->right = r;
                        res.push_back(node);
                    }
                }
            }
        }
        return res;
    }
};

void printnode(TreeNode* node) {
    if (node == nullptr) {
        cout << "null,";
        return;
    }
    cout << node->val << ",";
    printnode(node->left);
    printnode(node->right);
}

int main() {
    Solution s;
    vector<TreeNode*> res = s.allPossibleFBT(7);
    for (auto node : res) {
        cout << "[";
        printnode(node);
        cout << "]" << endl;
    }

    res = s.allPossibleFBT(3);
    for (auto node : res) {
        cout << "[";
        printnode(node);
        cout << "]" << endl;
    }

    return 0;
}