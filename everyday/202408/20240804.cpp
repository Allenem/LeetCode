/*
572. 另一棵树的子树

给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true ；否则，返回 false 。

二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。


示例 1：

输入：root = [3,4,5,1,2], subRoot = [4,1,2]
输出：true


示例 2：

输入：root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
输出：false
 

提示：

root 树上的节点数量范围是 [1, 2000]
subRoot 树上的节点数量范围是 [1, 1000]
-104 <= root.val <= 104
-104 <= subRoot.val <= 104
*/

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool dfs(TreeNode* root, TreeNode* subRoot) {
        if(root==nullptr || subRoot==nullptr)
            return root==subRoot;
        if(root->val!=subRoot->val) return false;
        return dfs(root->left, subRoot->left) && dfs(root->right, subRoot->right);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root==nullptr) return false;
        if(dfs(root, subRoot)) return true;
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};

int main() {
    Solution s;

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);

    TreeNode* subRoot = new TreeNode(4);
    subRoot->left = new TreeNode(1);
    subRoot->right = new TreeNode(2);

    cout << boolalpha << s.isSubtree(root, subRoot) << endl;

    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(4);
    root2->right = new TreeNode(5);
    root2->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(2);
    root2->left->right->left = new TreeNode(0);

    cout << boolalpha << s.isSubtree(root2, subRoot) << endl;

    return 0;
}