/*
2476. 二叉搜索树最近节点查询

给你一个 二叉搜索树 的根节点 root ，和一个由正整数组成、长度为 n 的数组 queries 。

请你找出一个长度为 n 的 二维 答案数组 answer ，其中 answer[i] = [mini, maxi] ：

mini 是树中小于等于 queries[i] 的 最大值 。如果不存在这样的值，则使用 -1 代替。
maxi 是树中大于等于 queries[i] 的 最小值 。如果不存在这样的值，则使用 -1 代替。
返回数组 answer 。

示例 1 ：

输入：root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14], queries = [2,5,16]
输出：[[2,2],[4,6],[15,-1]]
解释：按下面的描述找出并返回查询的答案：
- 树中小于等于 2 的最大值是 2 ，且大于等于 2 的最小值也是 2 。所以第一个查询的答案是 [2,2] 。
- 树中小于等于 5 的最大值是 4 ，且大于等于 5 的最小值是 6 。所以第二个查询的答案是 [4,6] 。
- 树中小于等于 16 的最大值是 15 ，且大于等于 16 的最小值不存在。所以第三个查询的答案是 [15,-1] 。

示例 2 ：

输入：root = [4,null,9], queries = [3]
输出：[[-1,4]]
解释：树中不存在小于等于 3 的最大值，且大于等于 3 的最小值是 4 。所以查询的答案是 [-1,4] 。

提示：

树中节点的数目在范围 [2, 105] 内
1 <= Node.val <= 106
n == queries.length
1 <= n <= 105
1 <= queries[i] <= 106
*/
#include <iostream>
#include <vector>
#include <algorithm>

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

    vector<int> s;

    void dfs(TreeNode* node) {
        if (!node) return;
        s.push_back(node->val);
        dfs(node->left);
        dfs(node->right);
    }

public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        vector<vector<int>> ans;
        dfs(root);
        sort(s.begin(), s.end());
        int in = s.front(), ax = s.back();
        for (auto v : queries) {
            vector<int> t(2);
            if (v < in) {
                t[0] = -1;
                t[1] = in;
            }
            else if (v > ax) {
                t[0] = ax;
                t[1] = -1;
            }
            else {
                auto l = lower_bound(s.begin(), s.end(), v);
                if (*l == v) t[0] = t[1] = v;
                else {
                    t[0] = *--l;
                    t[1] = *++l;
                }
            }
            ans.push_back(std::move(t));
        }
        return ans;
    }
};

int main() {
    Solution s1;
    vector<int> queries = { 2, 5, 16 };
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(13);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(15);
    root->right->right->left = new TreeNode(14);
    vector<vector<int>> ans = s1.closestNodes(root, queries);
    for (auto& v : ans) {
        cout << "[";
        for (auto& i : v) {
            cout << i << " ";
        }
        cout << "]";
    }
    cout << endl;

    Solution s2;
    vector<int> q = { 3 };
    TreeNode* root2 = new TreeNode(4);
    root2->right = new TreeNode(9);
    vector<vector<int>> ans2 = s2.closestNodes(root2, q);
    for (auto& v : ans2) {
        cout << "[";
        for (auto& i : v) {
            cout << i << " ";
        }
        cout << "]";
    }
    cout << endl;

    return 0;
}