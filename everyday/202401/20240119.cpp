/*
2809. 使数组和小于等于 x 的最少时间

给你两个长度相等下标从 0 开始的整数数组 nums1 和 nums2 。每一秒，对于所有下标 0 <= i < nums1.length ，nums1[i] 的值都增加 nums2[i] 。操作 完成后 ，你可以进行如下操作：

选择任一满足 0 <= i < nums1.length 的下标 i ，并使 nums1[i] = 0 。
同时给你一个整数 x 。

请你返回使 nums1 中所有元素之和 小于等于 x 所需要的 最少 时间，如果无法实现，那么返回 -1 。

示例 1：

输入：nums1 = [1,2,3], nums2 = [1,2,3], x = 4
输出：3
解释：
第 1 秒，我们对 i = 0 进行操作，得到 nums1 = [0,2+2,3+3] = [0,4,6] 。
第 2 秒，我们对 i = 1 进行操作，得到 nums1 = [0+1,0,6+3] = [1,0,9] 。
第 3 秒，我们对 i = 2 进行操作，得到 nums1 = [1+1,0+2,0] = [2,2,0] 。
现在 nums1 的和为 4 。不存在更少次数的操作，所以我们返回 3 。

示例 2：

输入：nums1 = [1,2,3], nums2 = [3,3,3], x = 4
输出：-1
解释：不管如何操作，nums1 的和总是会超过 x 。

提示：

1 <= nums1.length <= 103
1 <= nums1[i] <= 103
0 <= nums2[i] <= 103
nums1.length == nums2.length
0 <= x <= 106
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>

using namespace std;

class Solution1 {
public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n = nums1.size();
        vector<pair<int, int>> nums;
        // 从贪心的角度考虑，为了使得数组元素和的减少量最大，我们应当让 nums2 中的较大元素尽可能放在后面操作
        for (int i = 0;i < n;++i) nums.emplace_back(nums2[i], nums1[i]);
        sort(nums.begin(), nums.end());
        // dp: 对于数组 nums1 的前 i 个元素，进行 j 次操作，所能减少的数组元素和的最大值
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        for (auto [b, a] : nums) {
            for (int j = n;j;--j) {
                dp[j] = max(dp[j], dp[j - 1] + a + b * j);
            }
        }
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);
        for (int j = 0;j <= n;++j)
            if (s1 + s2 * j - dp[j] <= x) return j;
        return -1;
    }
};

class Solution2 {
public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n = nums1.size();
        vector<pair<int, int>> nums;
        // 从贪心的角度考虑，为了使得数组元素和的减少量最大，我们应当让 nums2 中的较大元素尽可能放在后面操作
        for (int i = 0;i < n;++i) nums.emplace_back(nums2[i], nums1[i]);
        sort(nums.begin(), nums.end());
        // dp: 对于数组 nums1 的前 i 个元素，进行 j 次操作，所能减少的数组元素和的最大值
        int dp[n + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 1;i <= n;++i) {
            for (int j = 0;j <= n;++j) {
                dp[i][j] = dp[i - 1][j];
                if (j) {
                    auto [b, a] = nums[i - 1];
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a + b * j);
                }
            }
        }
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);
        for (int j = 0;j <= n;++j)
            if (s1 + s2 * j - dp[n][j] <= x) return j;
        return -1;
    }
};

int main() {
    Solution1 solution1;
    Solution2 solution2;

    vector<int> nums1 = { 1, 2, 3 };
    vector<int> nums2 = { 1, 2, 3 };
    int x = 4;
    cout << solution1.minimumTime(nums1, nums2, x) << endl;
    cout << solution2.minimumTime(nums1, nums2, x) << endl;

    nums1 = { 1, 2, 3 };
    nums2 = { 3, 3, 3 };
    x = 4;
    cout << solution1.minimumTime(nums1, nums2, x) << endl;
    cout << solution2.minimumTime(nums1, nums2, x) << endl;

    return 0;
}