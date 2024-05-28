/*
2581. 统计可能的树根数目

Alice 有一棵 n 个节点的树，节点编号为 0 到 n - 1 。树用一个长度为 n - 1 的二维整数数组 edges 表示，其中 edges[i] = [ai, bi] ，表示树中节点 ai 和 bi 之间有一条边。

Alice 想要 Bob 找到这棵树的根。她允许 Bob 对这棵树进行若干次 猜测 。每一次猜测，Bob 做如下事情：

选择两个 不相等 的整数 u 和 v ，且树中必须存在边 [u, v] 。
Bob 猜测树中 u 是 v 的 父节点 。
Bob 的猜测用二维整数数组 guesses 表示，其中 guesses[j] = [uj, vj] 表示 Bob 猜 uj 是 vj 的父节点。

Alice 非常懒，她不想逐个回答 Bob 的猜测，只告诉 Bob 这些猜测里面 至少 有 k 个猜测的结果为 true 。

给你二维整数数组 edges ，Bob 的所有猜测和整数 k ，请你返回可能成为树根的 节点数目 。如果没有这样的树，则返回 0。

示例 1：

输入：edges = [[0,1],[1,2],[1,3],[4,2]], guesses = [[1,3],[0,1],[1,0],[2,4]], k = 3
输出：3
解释：
根为节点 0 ，正确的猜测为 [1,3], [0,1], [2,4]
根为节点 1 ，正确的猜测为 [1,3], [1,0], [2,4]
根为节点 2 ，正确的猜测为 [1,3], [1,0], [2,4]
根为节点 3 ，正确的猜测为 [1,0], [2,4]
根为节点 4 ，正确的猜测为 [1,3], [1,0]
节点 0 ，1 或 2 为根时，可以得到 3 个正确的猜测。

示例 2：

输入：edges = [[0,1],[1,2],[2,3],[3,4]], guesses = [[1,0],[3,4],[2,1],[3,2]], k = 1
输出：5
解释：
根为节点 0 ，正确的猜测为 [3,4]
根为节点 1 ，正确的猜测为 [1,0], [3,4]
根为节点 2 ，正确的猜测为 [1,0], [2,1], [3,4]
根为节点 3 ，正确的猜测为 [1,0], [2,1], [3,2], [3,4]
根为节点 4 ，正确的猜测为 [1,0], [2,1], [3,2]
任何节点为根，都至少有 1 个正确的猜测。

提示：

edges.length == n - 1
2 <= n <= 105
1 <= guesses.length <= 105
0 <= ai, bi, uj, vj <= n - 1
ai != bi
uj != vj
edges 表示一棵有效的树。
guesses[j] 是树中的一条边。
guesses 是唯一的。
0 <= k <= guesses.length
*/
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_set>

using namespace std;

using ll = long long;
class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        ll base = 1313131ll;
        vector<int> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        unordered_set<ll> vis;
        for (auto& gu : guesses) vis.emplace(gu[0] * base + gu[1]);

        // 以0为“根节点”，遍历该树，判断可以得到多少个父子对在guesses中。
        int ans = 0, cnt = 0;
        function<void(int, int)> dfs1 = [&](int fa, int x) {
            if (vis.count(fa * base + x)) cnt++;
            for (auto& y : g[x]) if (y != fa) dfs1(x, y);
            };
        dfs1(-1, 0);

        /*
        从0节点开始更换父节点到它的邻接点，我们发现只有更换父子节点的这对元素边的方向改变，
        其他边方向不变。这里多加一个参数c，是保证遍历当前节点的子节点时，当前节点的父子对数量
        对其他子节点不变。
        */
        function<void(int, int, int)> dfs2 = [&](int fa, int x, int c) {
            if (vis.count(fa * base + x)) c--;
            if (vis.count(x * base + fa)) c++;
            if (c >= k) ans++;
            for (auto& y : g[x]) if (y != fa) dfs2(x, y, c);
            };
        dfs2(-1, 0, cnt);

        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> edges = { {0, 1}, {1, 2}, {1, 3}, {4, 2} };
    vector<vector<int>> guesses = { {1, 3}, {0, 1}, {1, 0}, {2, 4} };
    cout << s.rootCount(edges, guesses, 3) << endl;

    edges = { {0, 1}, {1, 2}, {2, 3}, {3, 4} };
    guesses = { {1, 0}, {3, 4}, {2, 1}, {3, 2} };
    cout << s.rootCount(edges, guesses, 1) << endl;

    return 0;
}