/*
3266. K 次乘运算后的最终数组 II

给你一个整数数组 nums ，一个整数 k  和一个整数 multiplier 。

你需要对 nums 执行 k 次操作，每次操作中：

找到 nums 中的 最小 值 x ，如果存在多个最小值，选择最 前面 的一个。

将 x 替换为 x * multiplier 。

k 次操作以后，你需要将 nums 中每一个数值对 109 + 7 取余。

请你返回执行完 k 次乘运算以及取余运算之后，最终的 nums 数组。

 

示例 1：

输入：nums = [2,1,3,5,6], k = 5, multiplier = 2

输出：[8,4,6,5,6]

解释：

操作	结果
1 次操作后	[2, 2, 3, 5, 6]
2 次操作后	[4, 2, 3, 5, 6]
3 次操作后	[4, 4, 3, 5, 6]
4 次操作后	[4, 4, 6, 5, 6]
5 次操作后	[8, 4, 6, 5, 6]
取余操作后	[8, 4, 6, 5, 6]



示例 2：

输入：nums = [100000,2000], k = 2, multiplier = 1000000

输出：[999999307,999999993]

解释：

操作	结果
1 次操作后	[100000, 2000000000]
2 次操作后	[100000000000, 2000000000]
取余操作后	[999999307, 999999993]
 

提示：

1 <= nums.length <= 104
1 <= nums[i] <= 109
1 <= k <= 109
1 <= multiplier <= 106
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
// #include <ranges>
using namespace std;


class Solution {
    const int MOD = 1'000'000'007;

    long long pow(long long x, int n) {
        long long res = 1;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
        }
        return res;
    }

public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        if (multiplier == 1) { // 数组不变
            return move(nums);
        }

        int n = nums.size();
        int mx = ranges::max(nums);
        vector<pair<long long, int>> h(n);
        for (int i = 0; i < n; i++) {
            h[i] = {nums[i], i};
        }
        ranges::make_heap(h, greater<>()); // 最小堆，O(n) 堆化

        // 模拟，直到堆顶是 mx
        for (; k && h[0].first < mx; k--) {
            ranges::pop_heap(h, greater<>());
            h.back().first *= multiplier;
            ranges::push_heap(h, greater<>());
        }

        // 剩余的操作可以直接用公式计算
        ranges::sort(h);
        for (int i = 0; i < n; i++) {
            auto& [x, j] = h[i];
            nums[j] = x % MOD * pow(multiplier, k / n + (i < k % n)) % MOD;
        }
        return move(nums);
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/final-array-state-after-k-multiplication-operations-ii/solutions/2892178/zui-xiao-dui-mo-ni-shu-xue-gong-shi-pyth-z4zw/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution s;
    vector<int> nums = {2,1,3,5,6};
    int k = 5;
    int multiplier = 2;
    vector<int> res = s.getFinalState(nums, k, multiplier);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;

    nums = {100000,2000};
    k = 2;
    multiplier = 1000000;
    res = s.getFinalState(nums, k, multiplier);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}