/*
2846. 边权重均等查询

现有一棵由 n 个节点组成的无向树，节点按从 0 到 n - 1 编号。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ui, vi, wi] 表示树中存在一条位于节点 ui 和节点 vi 之间、权重为 wi 的边。

另给你一个长度为 m 的二维整数数组 queries ，其中 queries[i] = [ai, bi] 。对于每条查询，请你找出使从 ai 到 bi 路径上每条边的权重相等所需的 最小操作次数 。在一次操作中，你可以选择树上的任意一条边，并将其权重更改为任意值。

注意：

查询之间 相互独立 的，这意味着每条新的查询时，树都会回到 初始状态 。
从 ai 到 bi的路径是一个由 不同 节点组成的序列，从节点 ai 开始，到节点 bi 结束，且序列中相邻的两个节点在树中共享一条边。
返回一个长度为 m 的数组 answer ，其中 answer[i] 是第 i 条查询的答案。

示例 1：


输入：n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
输出：[0,0,1,3]
解释：第 1 条查询，从节点 0 到节点 3 的路径中的所有边的权重都是 1 。因此，答案为 0 。
第 2 条查询，从节点 3 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 0 。
第 3 条查询，将边 [2,3] 的权重变更为 2 。在这次操作之后，从节点 2 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 1 。
第 4 条查询，将边 [0,1]、[1,2]、[2,3] 的权重变更为 2 。在这次操作之后，从节点 0 到节点 6 的路径中的所有边的权重都是 2 。因此，答案为 3 。
对于每条查询 queries[i] ，可以证明 answer[i] 是使从 ai 到 bi 的路径中的所有边的权重相等的最小操作次数。

示例 2：


输入：n = 8, edges = [[1,2,6],[1,3,4],[2,4,6],[2,5,3],[3,6,6],[3,0,8],[7,0,2]], queries = [[4,6],[0,4],[6,5],[7,4]]
输出：[1,2,2,3]
解释：第 1 条查询，将边 [1,3] 的权重变更为 6 。在这次操作之后，从节点 4 到节点 6 的路径中的所有边的权重都是 6 。因此，答案为 1 。
第 2 条查询，将边 [0,3]、[3,1] 的权重变更为 6 。在这次操作之后，从节点 0 到节点 4 的路径中的所有边的权重都是 6 。因此，答案为 2 。
第 3 条查询，将边 [1,3]、[5,2] 的权重变更为 6 。在这次操作之后，从节点 6 到节点 5 的路径中的所有边的权重都是 6 。因此，答案为 2 。
第 4 条查询，将边 [0,7]、[0,3]、[1,3] 的权重变更为 6 。在这次操作之后，从节点 7 到节点 4 的路径中的所有边的权重都是 6 。因此，答案为 3 。
对于每条查询 queries[i] ，可以证明 answer[i] 是使从 ai 到 bi 的路径中的所有边的权重相等的最小操作次数。

提示：

1 <= n <= 104
edges.length == n - 1
edges[i].length == 3
0 <= ui, vi < n
1 <= wi <= 26
生成的输入满足 edges 表示一棵有效的树
1 <= queries.length == m <= 2 * 104
queries[i].length == 2
0 <= ai, bi < n
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// 图+层序遍历+LCA（Lowest Common Ancestor）
class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int m = 32 - __builtin_clz(n); // __builtin_clz(n) 计算 n 前导 0 的个数
        vector<pair<int, int>> g[n];   // 建图
        int f[n][m];                   // f[i][j] 表示节点 i 的第 2^j 个祖先。
        int p[n];                      // 父结点数组
        int cnt[n][26];                // cnt 存储根节点到目标节点 1-26权重边 出现的次数，因为题目给出权重1<=w<=26
        int depth[n];                  // 深度数组
        memset(f, 0, sizeof(f));
        memset(cnt, 0, sizeof(cnt));
        memset(depth, 0, sizeof(depth));
        memset(p, 0, sizeof(p));

        // 建图
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2] - 1; // 这里-1是为了w索引为0-25
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        // 层次遍历初始化各变量
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            f[i][0] = p[i]; // 从结点 i 走 i^0 步（f[i][0]）到达 i 的父结点（p[i]）
            for (int j = 1; j < m; ++j) {
                f[i][j] = f[f[i][j - 1]][j - 1]; // i的第j级祖先 -> i的上一级祖先的j-1级祖先
            }
            for (auto& [j, w] : g[i]) { // 遍历结点 i 的相邻结点
                if (j != p[i]) { // 不遍历结点 i 的父结点，即只遍历结点 i 的子结点
                    p[j] = i; // 完成 p[j] 的初始化，即结点 j 的父结点指向结点 i 
                    memcpy(cnt[j], cnt[i], sizeof(cnt[i])); // 结点 j 到根结点的边权计数在父结点 i 到根结点的边权计数基础上计算，因此先克隆一份
                    cnt[j][w]++;
                    depth[j] = depth[i] + 1;
                    q.push(j);
                }
            }
        }

        // 遍历 queries
        vector<int> ans;
        for (auto& qq : queries) {
            int u = qq[0], v = qq[1];
            int x = u, y = v;
            if (depth[x] < depth[y]) {
                swap(x, y);
            }
            // 重点 1，根据 f 数组先将 x 走到与 y 同层
            for (int j = m - 1; ~j; --j) {
                if (depth[x] - depth[y] >= (1 << j)) {
                    x = f[x][j];
                }
            }
            // 重点 2, 将已是同层的 x, y 继续向上走更新 x, y 直到 x, y 的公共祖先相同
            for (int j = m - 1; ~j; --j) {
                if (f[x][j] != f[y][j]) {
                    x = f[x][j];
                    y = f[y][j];
                }
            }
            // 如果重点 1 的循环已经得到了 x, y 不仅同层而且就是相同的结点，那么 x 就是最近的公共祖先
            // 否则会执行重点 2 里的if语句，这样更新后的 x, y 是不相同的，而是 x, y 的父结点是相同的。（可以画图试试看），此时会执行以下if语句，让 x 再走一步到 x, y 的父结点，也就是最近公共祖先。
            if (x != y) {
                x = p[x];
            }
            // 求权重众数w的最大出现次数，次数为 节点u的权重w出现次数 + 节点v的权重w出现次数 - 2 * 公共父节点x的权重w出现次数
            int mx = 0;
            for (int w = 0; w < 26; ++w) {
                mx = max(mx, cnt[u][w] + cnt[v][w] - 2 * cnt[x][w]);
            }
            // 求修改边数 = 节点u的深度 + 节点v的深度 - 2 * 公共父节点x的深度 - 不用修改的众数的出现次数
            ans.push_back(depth[u] + depth[v] - 2 * depth[x] - mx);
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> edges = { {0,1,1},{1,2,1},{2,3,1},{3,4,2},{4,5,2},{5,6,2} };
    vector<vector<int>> queries = { {0,3},{3,6},{2,6},{0,6} };
    vector<int> ans = s.minOperationsQueries(7, edges, queries);
    for (auto& a : ans) {
        cout << a << " ";
    }
    cout << endl;

    edges = { {1,2,6},{1,3,4},{2,4,6},{2,5,3},{3,6,6},{3,0,8},{7,0,2} };
    queries = { {4,6},{0,4},{6,5},{7,4} };
    ans = s.minOperationsQueries(8, edges, queries);
    for (auto& a : ans) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}