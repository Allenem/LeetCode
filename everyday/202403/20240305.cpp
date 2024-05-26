/*
1976. 到达目的地的方案数

你在一个城市里，城市由 n 个路口组成，路口编号为 0 到 n - 1 ，某些路口之间有 双向
道路。输入保证你可以从任意路口出发到达其他任意路口，且任意两个路口之间最多有一条路。

给你一个整数 n 和二维整数数组 roads ，其中 roads[i] = [ui, vi, timei] 表示在路口
ui 和 vi 之间有一条需要花费 timei 时间才能通过的道路。你想知道花费 最少时间
从路口 0 出发到达路口 n - 1 的方案数。

请返回花费 最少时间 到达目的地的 路径数目 。由于答案可能很大，将结果对 109 + 7
取余 后返回。

示例 1：

输入：n = 7, roads =
[[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
输出：4
解释：从路口 0 出发到路口 6 花费的最少时间是 7 分钟。
四条花费 7 分钟的路径分别为：
- 0 ➝ 6
- 0 ➝ 4 ➝ 6
- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

示例 2：

输入：n = 2, roads = [[1,0,10]]
输出：1
解释：只有一条从路口 0 到路口 1 的路，花费 10 分钟。

提示：

1 <= n <= 200
n - 1 <= roads.length <= n * (n - 1) / 2
roads[i].length == 3
0 <= ui, vi <= n - 1
1 <= timei <= 109
ui != vi
任意两个路口之间至多有一条路。
从任意路口出发，你能够到达其他任意路口。
*/

#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    static constexpr int MOD = 1E9 + 7;
    using PII = pair<int, int>;
    using PLI = pair<long long, int>;
    int countPaths(int n, vector<vector<int>>& roads) {
        // graph[u] (v, t): 与u节点连接的v节点，耗时t
        vector<vector<PII>> g(n);
        for (auto& r : roads) {
            g[r[0]].push_back(make_pair(r[1], r[2]));
            g[r[1]].push_back(make_pair(r[0], r[2]));
        }

        // dis:到达i点的最小距离
        // cnt:到达i点最小距离条数
        // see:是否已经经过i点了
        vector<long long> dis(n, LONG_LONG_MAX);
        vector<int> cnt(n, 0), see(n, 0);
        dis[0] = 0;
        cnt[0] = 1;

        // q (d, i): 优先队列，d距离，i节点。小顶堆
        priority_queue<PLI, vector<PLI>, greater<PLI>> q;
        q.emplace(0, 0);
        while (q.size()) {
            auto u = q.top().second;
            q.pop();
            if (see[u])
                continue;
            see[u] = 1;
            for (auto& [v, t] : g[u]) {
                if (dis[v] > dis[u] + t) {
                    cnt[v] = cnt[u];
                    dis[v] = dis[u] + t;
                    q.emplace(dis[v], v);
                } else if (dis[v] == dis[u] + t) {
                    cnt[v] = (cnt[v] + cnt[u]) % MOD;
                }
            }
        }
        return cnt[n - 1];
    }
};

int main() {
    Solution s;
    int n = 7;
    vector<vector<int>> roads = {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3},
                                 {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1},
                                 {0, 4, 5}, {4, 6, 2}};
    cout << s.countPaths(n, roads) << endl;

    n = 2;
    roads = {{1, 0, 10}};
    cout << s.countPaths(n, roads) << endl;
    return 0;
}