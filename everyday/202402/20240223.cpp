/*
2583. 二叉树中的第 K 大层和

给你一棵二叉树的根节点 root 和一个正整数 k 。

树中的 层和 是指 同一层 上节点值的总和。

返回树中第 k 大的层和（不一定不同）。如果树少于 k 层，则返回 -1 。

注意，如果两个节点与根节点的距离相同，则认为它们在同一层。

示例 1：

输入：root = [5,8,9,2,1,3,7,4,6], k = 2
输出：13
解释：树中每一层的层和分别是：
- Level 1: 5
- Level 2: 8 + 9 = 17
- Level 3: 2 + 1 + 3 + 7 = 13
- Level 4: 4 + 6 = 10
第 2 大的层和等于 13 。

示例 2：

输入：root = [1,2,null,3], k = 1
输出：3
解释：最大的层和是 3 。

提示：

树中的节点数为 n
2 <= n <= 105
1 <= Node.val <= 106
1 <= k <= n
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

using ll = long long;
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            ll cursum = 0;
            int n = q.size();
            while (n-- > 0) {
                TreeNode* node = q.front();
                cursum += node->val;
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right)q.push(node->right);
            }
            pq.push(cursum);
            if (pq.size() > k) pq.pop();
        }
        return (pq.size() < k) ? -1 : (pq.top());
    }
};

int main() {
    Solution sol;
    TreeNode a(5), b(8), c(9), d(2), e(1), f(3), g(7), h(4), i(6);
    a.left = &b; a.right = &c;
    b.left = &d; b.right = &e;
    c.left = &f; c.right = &g;
    d.left = &h; d.right = &i;
    cout << sol.kthLargestLevelSum(&a, 2) << endl;

    TreeNode a1(1), b1(2), c1(3);
    a1.left = &b1;
    b1.right = &c1;
    cout << sol.kthLargestLevelSum(&a1, 1) << endl;

    return 0;
}