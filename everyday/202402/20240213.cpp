/*
987. 二叉树的垂序遍历

给你二叉树的根结点 root ，请你设计算法计算二叉树的 垂序遍历 序列。

对位于 (row, col) 的每个结点而言，其左右子结点分别位于 (row + 1, col - 1) 和 (row + 1, col + 1) 。树的根结点位于 (0, 0) 。

二叉树的 垂序遍历 从最左边的列开始直到最右边的列结束，按列索引每一列上的所有结点，形成一个按出现位置从上到下排序的有序列表。如果同行同列上有多个结点，则按结点的值从小到大进行排序。

返回二叉树的 垂序遍历 序列。

示例 1：

输入：root = [3,9,20,null,null,15,7]
输出：[[9],[3,15],[20],[7]]
解释：
列 -1 ：只有结点 9 在此列中。
列  0 ：只有结点 3 和 15 在此列中，按从上到下顺序。
列  1 ：只有结点 20 在此列中。
列  2 ：只有结点 7 在此列中。

示例 2：

输入：root = [1,2,3,4,5,6,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
列 -2 ：只有结点 4 在此列中。
列 -1 ：只有结点 2 在此列中。
列  0 ：结点 1 、5 和 6 都在此列中。
          1 在上面，所以它出现在前面。
          5 和 6 位置都是 (2, 0) ，所以按值从小到大排序，5 在 6 的前面。
列  1 ：只有结点 3 在此列中。
列  2 ：只有结点 7 在此列中。

示例 3：

输入：root = [1,2,3,4,6,5,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
这个示例实际上与示例 2 完全相同，只是结点 5 和 6 在树中的位置发生了交换。
因为 5 和 6 的位置仍然相同，所以答案保持不变，仍然按值从小到大排序。

提示：

树中结点数目总数在范围 [1, 1000] 内
0 <= Node.val <= 1000
*/

#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <algorithm>
#include <climits>

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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<tuple<int, int, int>> nodes;
        function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int row, int col) {
            if (!node) return;
            nodes.emplace_back(col, row, node->val);
            dfs(node->left, row + 1, col - 1);
            dfs(node->right, row + 1, col + 1);
            };
        dfs(root, 0, 0);
        sort(nodes.begin(), nodes.end());
        vector<vector<int>> ans;
        int lastcol = INT_MIN;
        for (const auto& [col, row, val] : nodes) {
            if (col != lastcol) {
                lastcol = col;
                ans.emplace_back();
            }
            ans.back().push_back(val);
        }
        return ans;
    }
};

int main() {
    Solution s;
    TreeNode* root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    vector<vector<int>> ans = s.verticalTraversal(root);
    for (const auto& col : ans) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    TreeNode* root2 = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3, new TreeNode(6), new TreeNode(7)));
    vector<vector<int>> ans2 = s.verticalTraversal(root2);
    for (const auto& col : ans2) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    TreeNode* root3 = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(6)), new TreeNode(3, new TreeNode(5), new TreeNode(7)));
    vector<vector<int>> ans3 = s.verticalTraversal(root3);
    for (const auto& col : ans3) {
        for (const auto& val : col) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}