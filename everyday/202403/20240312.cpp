/*
1261. 在受污染的二叉树中查找元素

给出一个满足下述规则的二叉树：

root.val == 0
如果 treeNode.val == x 且 treeNode.left != null，那么 treeNode.left.val == 2 * x
+ 1 如果 treeNode.val == x 且 treeNode.right != null，那么 treeNode.right.val ==
2 * x + 2 现在这个二叉树受到「污染」，所有的 treeNode.val 都变成了 -1。

请你先还原二叉树，然后实现 FindElements 类：

FindElements(TreeNode* root) 用受污染的二叉树初始化对象，你需要先把它还原。
bool find(int target) 判断目标值 target 是否存在于还原后的二叉树中并返回结果。

示例 1：

输入：
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
输出：
[null,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1]);
findElements.find(1); // return False
findElements.find(2); // return True

示例 2：

输入：
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
输出：
[null,true,true,false]
解释：
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False

示例 3：

输入：
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
输出：
[null,true,false,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True

提示：

TreeNode.val == -1
二叉树的高度不超过 20
节点的总数在 [1, 10^4] 之间
调用 find() 的总次数在 [1, 10^4] 之间
0 <= target <= 10^6
*/
#include <iostream>
#include <queue>
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

class FindElements {
   public:
    vector<int> ans{0};
    FindElements(TreeNode* root) {
        root->val = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode* t = q.front();
                int v = t->val;
                q.pop();
                if (t->left) {
                    int lv = 2 * v + 1;
                    t->left->val = lv;
                    ans.push_back(lv);
                    q.push(t->left);
                }
                if (t->right) {
                    int rv = 2 * v + 2;
                    t->right->val = rv;
                    ans.push_back(rv);
                    q.push(t->right);
                }
            }
        }
    }

    bool find(int target) {
        for (int i : ans) {
            if (i == target)
                return true;
        }
        return false;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

int main() {
    TreeNode* root1 = new TreeNode(-1);
    root1->right = new TreeNode(-1);
    FindElements* obj1 = new FindElements(root1);
    cout << obj1->find(1) << endl;
    cout << obj1->find(2) << endl;

    TreeNode* root2 = new TreeNode(-1);
    root2->left = new TreeNode(-1);
    root2->right = new TreeNode(-1);
    root2->left->left = new TreeNode(-1);
    root2->left->right = new TreeNode(-1);
    FindElements* obj2 = new FindElements(root2);
    cout << obj2->find(1) << endl;
    cout << obj2->find(3) << endl;
    cout << obj2->find(5) << endl;

    TreeNode* root3 = new TreeNode(-1);
    root3->right = new TreeNode(-1);
    root3->right->left = new TreeNode(-1);
    root3->right->left->left = new TreeNode(-1);
    FindElements* obj3 = new FindElements(root3);
    cout << obj3->find(2) << endl;
    cout << obj3->find(3) << endl;
    cout << obj3->find(4) << endl;
    cout << obj3->find(5) << endl;

    return 0;
}