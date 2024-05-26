/*
322. 零钱兑换

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数
。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。

示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1

示例 2：

输入：coins = [2], amount = 3
输出：-1

示例 3：

输入：coins = [1], amount = 0
输出：0

提示：

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int coinChange(vector<int>& coins, int amount) {
        int MAX = amount + 1;
        vector<int> dp(amount + 1, MAX);
        dp[0] = 0;
        for (int j = 1; j <= amount; ++j) {
            for (int c : coins) {
                if (c <= j) {
                    dp[j] = min(dp[j], dp[j - c] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;
    vector<int> coins1 = {1, 2, 5};
    cout << sol.coinChange(coins1, 11) << endl;
    vector<int> coins2 = {2};
    cout << sol.coinChange(coins2, 3) << endl;
    vector<int> coins3 = {1};
    cout << sol.coinChange(coins3, 0) << endl;
    return 0;
}