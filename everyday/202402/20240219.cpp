/*
590. N 叉树的后序遍历

给定一个 n 叉树的根节点 root ，返回 其节点值的 后序遍历 。

n 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。

示例 1：

输入：root = [1,null,3,2,4,null,5,6]
输出：[5,6,3,2,4,1]

示例 2：

输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：[2,6,14,11,7,3,12,8,4,13,9,10,5,1]

提示：

节点总数在范围 [0, 104] 内
0 <= Node.val <= 104
n 叉树的高度小于或等于 1000

进阶：递归法很简单，你可以使用迭代法完成此题吗?
*/
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ret;
        function<void(Node*)> preorder = [&](Node* node) {
            if (!node) return;
            for (Node* ch : node->children)
                preorder(ch);
            ret.push_back(node->val);
            };
        preorder(root);
        return ret;
    }
};

int main() {
    Node* root = new Node(1);
    root->children.push_back(new Node(3));
    root->children.push_back(new Node(2));
    root->children.push_back(new Node(4));
    root->children[0]->children.push_back(new Node(5));
    root->children[0]->children.push_back(new Node(6));
    Solution s;
    vector<int> ret = s.postorder(root);
    for (int i : ret)
        cout << i << " ";
    cout << endl;


    Node* root2 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    root2->children.push_back(node2);
    root2->children.push_back(node3);
    root2->children.push_back(node4);
    root2->children.push_back(node5);
    Node* node6 = new Node(6);
    Node* node7 = new Node(7);
    Node* node8 = new Node(8);
    Node* node9 = new Node(9);
    Node* node10 = new Node(10);
    node3->children.push_back(node6);
    node3->children.push_back(node7);
    node4->children.push_back(node8);
    node5->children.push_back(node9);
    node5->children.push_back(node10);
    Node* node11 = new Node(11);
    Node* node12 = new Node(12);
    Node* node13 = new Node(13);
    node7->children.push_back(node11);
    node8->children.push_back(node12);
    node9->children.push_back(node13);
    Node* node14 = new Node(14);
    node11->children.push_back(node14);
    ret = s.postorder(root2);
    for (int i : ret)
        cout << i << " ";
    cout << endl;

    return 0;
}