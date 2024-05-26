/*
2952. 需要添加的硬币的最小数量

给你一个下标从 0 开始的整数数组 coins，表示可用的硬币的面值，以及一个整数 target
。

如果存在某个 coins 的子序列总和为 x，那么整数 x 就是一个 可取得的金额 。

返回需要添加到数组中的 任意面值 硬币的 最小数量 ，使范围 [1, target]
内的每个整数都属于 可取得的金额 。

数组的 子序列 是通过删除原始数组的一些（可能不删除）元素而形成的新的 非空
数组，删除过程不会改变剩余元素的相对位置。

示例 1：

输入：coins = [1,4,10], target = 19
输出：2
解释：需要添加面值为 2 和 8 的硬币各一枚，得到硬币数组 [1,2,4,8,10] 。
可以证明从 1 到 19
的所有整数都可由数组中的硬币组合得到，且需要添加到数组中的硬币数目最小为 2 。

示例 2：

输入：coins = [1,4,10,5,7,19], target = 19
输出：1
解释：只需要添加一枚面值为 2 的硬币，得到硬币数组 [1,2,4,5,7,10,19] 。
可以证明从 1 到 19
的所有整数都可由数组中的硬币组合得到，且需要添加到数组中的硬币数目最小为 1 。

示例 3：

输入：coins = [1,1,1], target = 20
输出：3
解释：
需要添加面值为 4 、8 和 16 的硬币各一枚，得到硬币数组 [1,1,1,4,8,16] 。
可以证明从 1 到 20
的所有整数都可由数组中的硬币组合得到，且需要添加到数组中的硬币数目最小为 3 。

提示：

1 <= target <= 105
1 <= coins.length <= 105
1 <= coins[i] <= target
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());
        int ans = 0;  // 要添加面额的最少次数
        int x = 1;    // 能否取到x
        int length = coins.size(), idx = 0;

        // 预先保证 [1, x-1] 能取到，新检查 coins[idx]
        while (x <= target) {
            if (idx < length && coins[idx] <= x) {
                // 取得到 x, 新区间 [1, x+c[i]-1]
                x += coins[idx];
                idx++;
            } else {
                // 取不到 x, 新加 x, 范围[1, 2x-1]
                x <<= 1;
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> coins1 = {1, 4, 10};
    cout << sol.minimumAddedCoins(coins1, 19) << endl;
    vector<int> coins2 = {1, 4, 10, 5, 7, 19};
    cout << sol.minimumAddedCoins(coins2, 19) << endl;
    vector<int> coins3 = {1, 1, 1};
    cout << sol.minimumAddedCoins(coins3, 20) << endl;
    return 0;
}