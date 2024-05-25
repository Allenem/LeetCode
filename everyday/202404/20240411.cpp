/*
1766. 互质树

给你一个 n 个节点的树（也就是一个无环连通无向图），节点编号从 0 到 n - 1
，且恰好有 n - 1 条边，每个节点有一个值。树的 根节点 为 0 号点。

给你一个整数数组 nums 和一个二维数组 edges 来表示这棵树。nums[i] 表示第 i
个点的值，edges[j] = [uj, vj] 表示节点 uj 和节点 vj 在树中有一条边。

当 gcd(x, y) == 1 ，我们称两个数 x 和 y 是 互质的 ，其中 gcd(x, y) 是 x 和 y 的
最大公约数 。

从节点 i 到 根 最短路径上的点都是节点 i 的祖先节点。一个节点 不是
它自己的祖先节点。

请你返回一个大小为 n 的数组 ans ，其中 ans[i]是离节点 i 最近的祖先节点且满足
nums[i] 和 nums[ans[i]] 是 互质的 ，如果不存在这样的祖先节点，ans[i] 为 -1 。

示例 1：

输入：nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
输出：[-1,0,0,1]
解释：上图中，每个节点的值在括号中表示。
- 节点 0 没有互质祖先。
- 节点 1 只有一个祖先节点 0 。它们的值是互质的（gcd(2,3) == 1）。
- 节点 2 有两个祖先节点，分别是节点 1 和节点 0 。节点 1
的值与它的值不是互质的（gcd(3,3) == 3）但节点 0 的值是互质的(gcd(2,3) ==
1)，所以节点 0 是最近的符合要求的祖先节点。
- 节点 3 有两个祖先节点，分别是节点 1 和节点 0 。它与节点 1 互质（gcd(3,2) ==
1），所以节点 1 是离它最近的符合要求的祖先节点。

示例 2：

输入：nums = [5,6,10,2,3,6,15], edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
输出：[-1,0,-1,0,0,0,-1]

提示：

nums.length == n
1 <= nums[i] <= 50
1 <= n <= 105
edges.length == n - 1
edges[j].length == 2
0 <= uj, vj < n
uj != vj
*/

#include <algorithm>
#include <iostream>
#include <numeric>  // for std::gcd
#include <stack>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> G;
    stack<pair<int, int>> last[55];
    vector<int> ret;

   public:
    void dfs(int node, int pre, int depth, vector<int>& nums) {
        int mom = -1, dep = -1;
        // Find the most recent ancestor that is coprime with nums[node]
        for (int i = 1; i <= 50; ++i) {
            if (!last[i].empty() && last[i].top().second > dep &&
                gcd(i, nums[node]) == 1) {
                mom = last[i].top().first;
                dep = last[i].top().second;
            }
        }
        ret[node] = mom;
        // Traverse the adjacency list
        for (int g : G[node]) {
            if (g != pre) {
                last[nums[node]].push({node, depth});
                dfs(g, node, depth + 1, nums);
                last[nums[node]].pop();
            }
        }
    }

    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        G.clear();
        G.resize(n);
        ret.clear();
        ret.assign(n, -1);  // Initialize ret with -1 for each node

        for (auto& e : edges) {
            G[e[0]].push_back(e[1]);
            G[e[1]].push_back(e[0]);
        }
        dfs(0, -1, 0, nums);
        return ret;
    }
};

int main() {
    Solution s;
    vector<int> nums = {2, 3, 3, 2};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
    vector<int> ans = s.getCoprimes(nums, edges);
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;

    nums = {5, 6, 10, 2, 3, 6, 15};
    edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
    ans = s.getCoprimes(nums, edges);
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
