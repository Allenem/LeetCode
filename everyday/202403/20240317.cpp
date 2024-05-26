/*
310. 最小高度树

树是一个无向图，其中任何两个顶点只通过一条路径连接。
换句话说，任何一个没有简单环路的连通图都是一棵树。

给你一棵包含 n 个节点的树，标记为 0 到 n - 1 。给定数字 n 和一个有 n - 1
条无向边的 edges 列表（每一个边都是一对标签），其中 edges[i] = [ai, bi]
表示树中节点 ai 和 bi 之间存在一条无向边。

可选择树中任何一个节点作为根。当选择节点 x 作为根节点时，设结果树的高度为 h
。在所有可能的树中，具有最小高度的树（即，min(h)）被称为 最小高度树 。

请你找到所有的 最小高度树 并按 任意顺序 返回它们的根节点标签列表。

树的 高度 是指根节点和叶子节点之间最长向下路径上边的数量。

示例 1：

输入：n = 4, edges = [[1,0],[1,2],[1,3]]
输出：[1]
解释：如图所示，当根是标签为 1 的节点时，树的高度是 1 ，这是唯一的最小高度树。

示例 2：

输入：n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
输出：[3,4]

提示：

1 <= n <= 2 * 104
edges.length == n - 1
0 <= ai, bi < n
ai != bi
所有 (ai, bi) 互不相同
给定的输入 保证 是一棵树，并且 不会有重复的边
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1)
            return {0};

        vector<int> degree(
            n);  // 每个节点对应的度数，因为是无向图，所以出入度一起统计
        vector<vector<int>> mp(n);  // 每个节点的邻接表
        vector<int> ans;            // 结果

        for (int i = 0; i < edges.size(); i++) {  // 统计每个节点的度数
            int u = edges[i][0];
            int v = edges[i][1];
            degree[u]++;
            degree[v]++;
            mp[u].emplace_back(v);
            mp[v].emplace_back(u);
        }

        // 从度为1开始bfs
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                q.push(i);  // 把叶子节点（度为1）入队列
            }
        }
        while (!q.empty()) {
            ans.clear();
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int node = q.front();
                q.pop();
                ans.emplace_back(node);
                degree[node]--;
                for (int j : mp[node]) {
                    degree[j]--;
                    if (degree[j] == 1) {
                        q.push(j);  // 新的度为1的节点加入队列
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{1, 0}, {1, 2}, {1, 3}};
    vector<int> ans = sol.findMinHeightTrees(4, edges);
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;

    edges = {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
    ans = sol.findMinHeightTrees(6, edges);
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}