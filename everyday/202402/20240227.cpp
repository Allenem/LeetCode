/*
2867. 统计树中的合法路径数目

给你一棵 n 个节点的无向树，节点编号为 1 到 n 。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ui, vi] 表示节点 ui 和 vi 在树中有一条边。

请你返回树中的 合法路径数目 。

如果在节点 a 到节点 b 之间 恰好有一个 节点的编号是质数，那么我们称路径 (a, b) 是 合法的 。

注意：

路径 (a, b) 指的是一条从节点 a 开始到节点 b 结束的一个节点序列，序列中的节点 互不相同 ，且相邻节点之间在树上有一条边。
路径 (a, b) 和路径 (b, a) 视为 同一条 路径，且只计入答案 一次 。


示例 1：

输入：n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
输出：4
解释：恰好有一个质数编号的节点路径有：
- (1, 2) 因为路径 1 到 2 只包含一个质数 2 。
- (1, 3) 因为路径 1 到 3 只包含一个质数 3 。
- (1, 4) 因为路径 1 到 4 只包含一个质数 2 。
- (2, 4) 因为路径 2 到 4 只包含一个质数 2 。
只有 4 条合法路径。

示例 2：

输入：n = 6, edges = [[1,2],[1,3],[2,4],[3,5],[3,6]]
输出：6
解释：恰好有一个质数编号的节点路径有：
- (1, 2) 因为路径 1 到 2 只包含一个质数 2 。
- (1, 3) 因为路径 1 到 3 只包含一个质数 3 。
- (1, 4) 因为路径 1 到 4 只包含一个质数 2 。
- (1, 6) 因为路径 1 到 6 只包含一个质数 3 。
- (2, 4) 因为路径 2 到 4 只包含一个质数 2 。
- (3, 6) 因为路径 3 到 6 只包含一个质数 3 。
只有 6 条合法路径。

提示：

1 <= n <= 105
edges.length == n - 1
edges[i].length == 2
1 <= ui, vi <= n
输入保证 edges 形成一棵合法的树。
*/

#include <iostream>
#include <vector>
#include <functional>
#include <cstring>

using namespace std;

#define MAXN ((int) 1e5)
class Solution {
public:
    long long countPaths(int n, vector<vector<int>>& edges) {
        // 筛选合数true，质数false
        bool flag[MAXN + 10];
        memset(flag, 0, sizeof(flag));
        flag[0] = flag[1] = true;
        for (int i = 2; i * i <= MAXN; ++i) if (!flag[i]) for (int j = i << 1; j <= MAXN; j += i) flag[j] = true;

        // 建图
        vector<int> e[n + 1];
        for (auto& edge : edges) {
            e[edge[0]].push_back(edge[1]);
            e[edge[1]].push_back(edge[0]);
        }

        long long ans = 0;
        // fu  表示以节点 u 为起点，以 u 的子树中某个节点为终点的路径中，所有点编号都是合数的路径有几条。
        // gu  表示以节点 u 为起点，以 u 的子树中某个节点为终点的路径中，有一个点的编号为质数的路径有几条。
        int f[n + 1], g[n + 1];

        // 树dp
        function<void(int, int)> dfs = [&](int i, int j) {
            if (flag[j]) f[j] = 1, g[j] = 0;
            else f[j] = 0, g[j] = 1;

            for (int k : e[j]) if (k != i) {
                dfs(j, k);
                // 路径上深度最低的节点为 j，这样的合法路径有几条
                ans += f[j] * g[k] + f[k] * g[j];
                // 更新以 j 为起点，且走到子树里的路径数量
                if (flag[j]) {
                    f[j] += f[k];
                    g[j] += g[k];
                }
                else {
                    g[j] += f[k];
                }
            }
            };

        dfs(0, 1);
        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> edges = { {1,2},{1,3},{2,4},{2,5} };
    cout << s.countPaths(5, edges) << endl;

    vector<vector<int>> edges2 = { {1,2},{1,3},{2,4},{3,5},{3,6} };
    cout << s.countPaths(6, edges2) << endl;
}