/*
410. 分割数组的最大值

给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组。

设计一个算法使得这 k 个子数组各自和的最大值最小。

示例 1：

输入：nums = [7,2,5,10,8], k = 2
输出：18
解释：
一共有四种方法将 nums 分割为 2 个子数组。
其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。

示例 2：

输入：nums = [1,2,3,4,5], k = 2
输出：9

示例 3：

输入：nums = [1,4,4], k = 3
输出：4

提示：

1 <= nums.length <= 1000
0 <= nums[i] <= 106
1 <= k <= min(50, nums.length)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

class Solution1 {
public:
    int splitArray(vector<int>& nums, int m) {
        using ll = long long;
        int n = nums.size();
        // dp[i][j] 表示前i个分为j个数组最小的最大值
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, LLONG_MAX));
        dp[0][0] = 0;
        // 前缀和
        vector<ll> presum(n + 1, 0);
        for (int i = 1;i <= n;++i)
            presum[i] += presum[i - 1] + nums[i - 1];
        for (int i = 1;i <= n;++i) {
            for (int j = 1;j <= min(i, m);++j) {
                for (int k = 0;k < i;++k) {
                    dp[i][j] = min(dp[i][j], max(dp[k][j - 1], presum[i] - presum[k]));
                }
            }
        }
        return (int)dp[n][m];
    }
};

class Solution2 {
public:
    int splitArray(vector<int>& nums, int k) {
        auto check = [&](int mx) -> bool {
            int cnt = 1, s = 0;
            for (int x : nums) {
                if (s + x <= mx) {
                    s += x;
                }
                else { // 新划分一段
                    if (cnt++ == k) {
                        return false;
                    }
                    s = x;
                }
            }
            return true;
            };

        // 右边界：所有元素和sum
        int right = accumulate(nums.begin(), nums.end(), 0);
        // 左边界：1.nums中最大数-1，不可能；2.均值sum/k向下取整，也不可能
        int left = max(*ranges::max_element(nums) - 1, (right - 1) / k);
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};

int main() {
    Solution1 sol1;
    Solution2 sol2;

    vector<int> nums = { 7,2,5,10,8 };
    int k = 2;
    cout << sol1.splitArray(nums, k) << endl;
    cout << sol2.splitArray(nums, k) << endl;

    nums = { 1,2,3,4,5 };
    k = 2;
    cout << sol1.splitArray(nums, k) << endl;
    cout << sol2.splitArray(nums, k) << endl;

    nums = { 1,4,4 };
    k = 3;
    cout << sol1.splitArray(nums, k) << endl;
    cout << sol2.splitArray(nums, k) << endl;

    return 0;
}

// g++ 20240121.cpp -std=c++20