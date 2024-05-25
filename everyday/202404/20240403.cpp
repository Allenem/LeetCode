/*
1379. 找出克隆二叉树中的相同节点

给你两棵二叉树，原始树 original 和克隆树 cloned，以及一个位于原始树 original
中的目标节点 target。

其中，克隆树 cloned 是原始树 original 的一个 副本 。

请找出在树 cloned 中，与 target 相同 的节点，并返回对该节点的引用（在 C/C++
等有指针的语言中返回 节点指针，其他语言返回节点本身）。

注意：你 不能 对两棵二叉树，以及 target 节点进行更改。只能 返回对克隆树 cloned
中已有的节点的引用。

示例 1:

输入: tree = [7,4,3,null,null,6,19], target = 3
输出: 3
解释: 上图画出了树 original 和 cloned。target 节点在树 original
中，用绿色标记。答案是树 cloned 中的黄颜色的节点（其他示例类似）。

示例 2:

输入: tree = [7], target =  7
输出: 7

示例 3:

输入: tree = [8,null,6,null,5,null,4,null,3,null,2,null,1], target = 4
输出: 4

提示：

树中节点的数量范围为 [1, 104] 。
同一棵树中，没有值相同的节点。
target 节点是树 original 中的一个节点，并且不会是 null 。
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
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    TreeNode* getTargetCopy(TreeNode* original,
                            TreeNode* cloned,
                            TreeNode* target) {
        return original == NULL || original == target ? cloned
               : getTargetCopy(original->left, cloned->left, target) != NULL
                   ? getTargetCopy(original->left, cloned->left, target)
                   : getTargetCopy(original->right, cloned->right, target);
    }
};

int main() {
    Solution s;
    TreeNode* original = new TreeNode(7);
    original->left = new TreeNode(4);
    original->right = new TreeNode(3);
    original->right->left = new TreeNode(6);
    original->right->right = new TreeNode(19);
    TreeNode* cloned = new TreeNode(7);
    cloned->left = new TreeNode(4);
    cloned->right = new TreeNode(3);
    cloned->right->left = new TreeNode(6);
    cloned->right->right = new TreeNode(19);
    TreeNode* target = original->right;
    cout << s.getTargetCopy(original, cloned, target)->val << endl;

    original = new TreeNode(7);
    cloned = new TreeNode(7);
    target = original;
    cout << s.getTargetCopy(original, cloned, target)->val << endl;

    original = new TreeNode(8);
    original->right = new TreeNode(6);
    original->right->right = new TreeNode(5);
    original->right->right->right = new TreeNode(4);
    original->right->right->right->right = new TreeNode(3);
    original->right->right->right->right->right = new TreeNode(2);
    original->right->right->right->right->right->right = new TreeNode(1);
    cloned = new TreeNode(8);
    cloned->right = new TreeNode(6);
    cloned->right->right = new TreeNode(5);
    cloned->right->right->right = new TreeNode(4);
    cloned->right->right->right->right = new TreeNode(3);
    cloned->right->right->right->right->right = new TreeNode(2);
    cloned->right->right->right->right->right->right = new TreeNode(1);
    target = original->right->right->right;
    cout << s.getTargetCopy(original, cloned, target)->val << endl;

    return 0;
}