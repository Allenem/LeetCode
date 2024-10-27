/*
684. 冗余连接

树可以看成是一个连通且 无环 的 无向 图。

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。



示例 1：

1---2
|  /
| /
3

输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]



示例 2：

2---1---5
|   |
3---4

输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]
 

提示:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges 中无重复元素
给定的图是连通的 
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
    vector<int> parents;

public:
    Solution() : parents(1001) { // 假设边的数量不会超过 1000
        iota(parents.begin(), parents.end(), 0); // 使用iota初始化
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        for (auto& edge : edges) {
            if (find(edge[0]) != find(edge[1])) 
                unite(edge[0], edge[1]);
            else 
                return edge;
        }
        return {};  // 默认返回值，防止无返回值的情况
    }

private:
    int find(int idx) {
        if (parents[idx] != idx) 
            parents[idx] = find(parents[idx]); // 路径压缩
        return parents[idx];
    }

    void unite(int n1, int n2) {
        parents[find(n1)] = find(n2);
    }
};

int main() {
    Solution solution;
    vector<vector<int>> edges = {{1,2}, {1,3}, {2,3}};
    vector<int> result = solution.findRedundantConnection(edges);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    edges = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    result = solution.findRedundantConnection(edges);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}