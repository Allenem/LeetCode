/*
429. N 叉树的层序遍历

给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。

树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。

示例 1：

输入：root = [1,null,3,2,4,null,5,6]
输出：[[1],[3,2,4],[5,6]]

示例 2：

输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：[[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

提示：

树的高度不会超过 1000
树的节点总数在 [0, 104] 之间
*/
#include <iostream>
#include <vector>
#include <deque>

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
    vector<vector<int>> levelOrder(Node* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        deque<Node*> dq;
        dq.push_back(root);
        while (!dq.empty()) {
            vector<int> tmp;
            int sz = dq.size();
            for (int i = 0;i < sz;++i) {
                Node* node = dq.front();
                dq.pop_front();
                tmp.push_back(node->val);
                if (!node->children.empty())
                    for (Node* child : node->children) {
                        if (child)dq.push_back(child);
                    }
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};

int main() {
    Solution s;
    Node* root = new Node(1);
    Node* node1 = new Node(3);
    Node* node2 = new Node(2);
    Node* node3 = new Node(4);
    root->children.push_back(node1);
    root->children.push_back(node2);
    root->children.push_back(node3);
    Node* node4 = new Node(5);
    Node* node5 = new Node(6);
    node1->children.push_back(node4);
    node1->children.push_back(node5);
    vector<vector<int>> res = s.levelOrder(root);
    for (auto& v : res) {
        for (int i : v) {
            cout << i << ' ';
        }
        cout << endl;
    }
    cout << endl;

    Node* root2 = new Node(1);
    node2 = new Node(2);
    node3 = new Node(3);
    node4 = new Node(4);
    node5 = new Node(5);
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

    vector<vector<int>> res2 = s.levelOrder(root2);
    for (auto& v : res2) {
        for (int i : v) {
            cout << i << ' ';
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}