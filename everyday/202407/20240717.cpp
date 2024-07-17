/*
2959. 关闭分部的可行集合数目

一个公司在全国有 n 个分部，它们之间有的有道路连接。一开始，所有分部通过这些道路两两之间互相可以到达。

公司意识到在分部之间旅行花费了太多时间，所以它们决定关闭一些分部（也可能不关闭任何分部），同时保证剩下的分部之间两两互相可以到达且最远距离不超过 maxDistance 。

两个分部之间的 距离 是通过道路长度之和的 最小值 。

给你整数 n ，maxDistance 和下标从 0 开始的二维整数数组 roads ，其中 roads[i] = [ui, vi, wi] 表示一条从 ui 到 vi 长度为 wi的 无向 道路。

请你返回关闭分部的可行方案数目，满足每个方案里剩余分部之间的最远距离不超过 maxDistance。

注意，关闭一个分部后，与之相连的所有道路不可通行。

注意，两个分部之间可能会有多条道路。

示例 1：

(0) --- 2 --- (1)
|             /
|           /
10        10
|       /
|     /
(2)

输入：n = 3, maxDistance = 5, roads = [[0,1,2],[1,2,10],[0,2,10]]
输出：5
解释：可行的关闭分部方案有：
- 关闭分部集合 [2] ，剩余分部为 [0,1] ，它们之间的距离为 2 。
- 关闭分部集合 [0,1] ，剩余分部为 [2] 。
- 关闭分部集合 [1,2] ，剩余分部为 [0] 。
- 关闭分部集合 [0,2] ，剩余分部为 [1] 。
- 关闭分部集合 [0,1,2] ，关闭后没有剩余分部。
总共有 5 种可行的关闭方案。

示例 2：

 ------ 20 ------
|               |
(0) --- 10 --- (1)
|               /
|             /
2           2
|         /
|       /
(2)

输入：n = 3, maxDistance = 5, roads = [[0,1,20],[0,1,10],[1,2,2],[0,2,2]]
输出：7
解释：可行的关闭分部方案有：
- 关闭分部集合 [] ，剩余分部为 [0,1,2] ，它们之间的最远距离为 4 。
- 关闭分部集合 [0] ，剩余分部为 [1,2] ，它们之间的距离为 2 。
- 关闭分部集合 [1] ，剩余分部为 [0,2] ，它们之间的距离为 2 。
- 关闭分部集合 [0,1] ，剩余分部为 [2] 。
- 关闭分部集合 [1,2] ，剩余分部为 [0] 。
- 关闭分部集合 [0,2] ，剩余分部为 [1] 。
- 关闭分部集合 [0,1,2] ，关闭后没有剩余分部。
总共有 7 种可行的关闭方案。

示例 3：

输入：n = 1, maxDistance = 10, roads = []
输出：2
解释：可行的关闭分部方案有：
- 关闭分部集合 [] ，剩余分部为 [0] 。
- 关闭分部集合 [0] ，关闭后没有剩余分部。
总共有 2 种可行的关闭方案。

提示：

1 <= n <= 10
1 <= maxDistance <= 105
0 <= roads.length <= 1000
roads[i].length == 3
0 <= ui, vi <= n - 1
ui != vi
1 <= wi <= 1000
一开始所有分部之间通过道路互相可以到达。
*/
#include <vector>
#include <iostream>
#include <functional>
#include <cstring>

using namespace std;

class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        const int N = 15;
        int g[N][N];
        int total = (1 << n) - 1;

        function<int(int)> check = [&](int subset) {
            memset(g, 0x3f, sizeof(g));
            int remain = total ^ subset;
            for (auto& edge : roads) {
                int u = edge[0], v = edge[1], w = edge[2];
                if ((subset >> u & 1) || (subset >> v & 1)) continue;
                // 注意重边
                g[u][v] = min(g[u][v], w);
                g[v][u] = min(g[v][u], w);
            }
            for (int i = 0; i < n; i++) {
                g[i][i] = 0;
            }
            int ans = 0;
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if ((remain >> i & 1) && (remain >> j & 1)) {
                        if (g[i][j] > maxDistance) {
                            return 0;
                        }
                    }
                }
            }
            return 1;
            };

        int ans = 0;
        for (int mask = 0; mask <= total; mask++) {
            // 枚举删除的节点
            ans += check(mask);
        }
        return ans;
    }
};

int main() {
    Solution s;
    for (auto& [n, maxDistance, roads] : vector<tuple<int, int, vector<vector<int>>>>{
        {3, 5, {{0,1,2},{1,2,10},{0,2,10}}},
        {3, 5, {{0,1,20},{0,1,10},{1,2,2},{0,2,2}}},
        {1, 10, {}}
        }) {
        cout << s.numberOfSets(n, maxDistance, roads) << endl;
    }
    return 0;
}
