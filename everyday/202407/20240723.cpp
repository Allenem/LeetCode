/*
3098. 求出所有子序列的能量和

给你一个长度为 n 的整数数组 nums 和一个 正 整数 k 。一个 子序列  的 能量 定义为子序列中 任意 两个元素的差值绝对值的 最小值 。

请你返回 nums 中长度 等于 k 的 所有 子序列的 能量和 。

由于答案可能会很大，将答案对 109 + 7 取余 后返回。



示例 1：

输入：nums = [1,2,3,4], k = 3

输出：4

解释：

nums 中总共有 4 个长度为 3 的子序列：[1,2,3] ，[1,3,4] ，[1,2,4] 和 [2,3,4] 。能量和为 |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4 。



示例 2：

输入：nums = [2,2], k = 2

输出：0

解释：

nums 中唯一一个长度为 2 的子序列是 [2,2] 。能量和为 |2 - 2| = 0 。



示例 3：

输入：nums = [4,3,-1], k = 2

输出：10

解释：

nums 总共有 3 个长度为 2 的子序列：[4,3] ，[4,-1] 和 [3,-1] 。能量和为 |4 - 3| + |4 - (-1)| + |3 - (-1)| = 10 。



提示：

2 <= n == nums.length <= 50
-108 <= nums[i] <= 108
2 <= k <= n
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size();
        const int MOD = 1e9 + 7, INF = 1e9;
        unordered_map<string, int> dp;
        sort(nums.begin(), nums.end());

        function<int(int, int, int, int)> dfs = [&](int curi, int lasti, int cnt, int mindiff) -> int {
            if (cnt > k || cnt + n - curi < k || mindiff == 0) return 0;
            if (curi == n) {
                if (cnt == k) return mindiff % MOD;
                return 0;
            }

            string state = to_string(curi) + "#" + to_string(lasti) + "#" + to_string(cnt) + "#" + to_string(mindiff);
            if (dp.count(state)) return dp[state];

            int ret = dfs(curi + 1, lasti, cnt, mindiff) % MOD; // exclude curi
            ret = (ret + dfs(curi + 1, curi, cnt + 1, min(mindiff, (lasti != -1 ? nums[curi] - nums[lasti] : INF)))) % MOD; // include curi
            return dp[state] = ret;
            };

        return dfs(0, -1, 0, INF);
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums = {
        {1,2,3,4},
        {2,2},
        {4,3,-1}
    };
    vector<int> k = { 3, 2, 2 };
    for (int i = 0; i < nums.size(); i++) {
        cout << s.sumOfPowers(nums[i], k[i]) << endl;
    }
    return 0;
}