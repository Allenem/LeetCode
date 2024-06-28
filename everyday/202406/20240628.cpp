/*
2742. 给墙壁刷油漆

给你两个长度为 n 下标从 0 开始的整数数组 cost 和 time ，分别表示给 n 堵不同的墙刷油漆需要的开销和时间。你有两名油漆匠：

一位需要 付费 的油漆匠，刷第 i 堵墙需要花费 time[i] 单位的时间，开销为 cost[i] 单位的钱。
一位 免费 的油漆匠，刷 任意 一堵墙的时间为 1 单位，开销为 0 。但是必须在付费油漆匠 工作 时，免费油漆匠才会工作。
请你返回刷完 n 堵墙最少开销为多少。

示例 1：

输入：cost = [1,2,3,2], time = [1,2,3,2]
输出：3
解释：下标为 0 和 1 的墙由付费油漆匠来刷，需要 3 单位时间。同时，免费油漆匠刷下标为 2 和 3 的墙，需要 2 单位时间，开销为 0 。总开销为 1 + 2 = 3 。

示例 2：

输入：cost = [2,3,4,2], time = [1,1,1,1]
输出：4
解释：下标为 0 和 3 的墙由付费油漆匠来刷，需要 2 单位时间。同时，免费油漆匠刷下标为 1 和 2 的墙，需要 2 单位时间，开销为 0 。总开销为 2 + 2 = 4 。

提示：

1 <= cost.length <= 500
cost.length == time.length
1 <= cost[i] <= 10^6
1 <= time[i] <= 500
*/
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class Solution {
public:
    // 方法一：记忆化搜索
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<vector<int>> f(n, vector<int>(2 * n + 1, -1));
        // 函数 dfs(i,j)，表示从第 i 堵墙开始，且当前剩余的免费油漆匠工作时间为 j 时，刷完剩余所有墙壁的最小开销。那么答案为 dfs(0,0)。
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            // 如果 n−i≤j，表示剩余的墙壁不超过免费油漆匠的工作时间，那么剩余的墙壁都由免费油漆匠刷，开销为 0；
            if (n - i <= j - n) return 0;
            // 如果 i≥n，返回 +∞；
            if (i >= n) return 1 << 30;
            // 否则
            // 如果第 i 堵墙由付费油漆匠刷，开销为 cost[i]，那么 dfs(i,j)=dfs(i+1,j+time[i])+cost[i]；
            // 如果第 i 堵墙由免费油漆匠刷，开销为 0，      那么 dfs(i,j)=dfs(i+1,j−1)。
            if (f[i][j] == -1) f[i][j] = min(dfs(i + 1, j + time[i]) + cost[i], dfs(i + 1, j - 1));
            return f[i][j];
            };
        // 参数 j 可能小于 0，因此，在实际编码过程中，除了 Python 语言外，我们对 j 加上一个偏移量 n，使得 j 的取值范围为 [0,2n]
        return dfs(0, n);
    }
};

int main() {
    Solution solution;
    for (auto [cost, time] : vector<pair<vector<int>, vector<int>>>{
        {{1,2,3,2}, {1,2,3,2}},
        {{2,3,4,2}, {1,1,1,1}}
        }) {
        cout << solution.paintWalls(cost, time) << endl;
    }
    return 0;
}