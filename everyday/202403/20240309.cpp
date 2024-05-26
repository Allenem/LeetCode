/*
2386. 找出数组的第 K 大和

给你一个整数数组 nums 和一个 正 整数 k 。你可以选择数组的任一 子序列
并且对其全部元素求和。

数组的 第 k 大和 定义为：可以获得的第 k 个 最大 子序列和（子序列和允许出现重复）

返回数组的 第 k 大和 。

子序列是一个可以由其他数组删除某些或不删除元素派生而来的数组，且派生过程不改变剩余元素的顺序。

注意：空子序列的和视作 0 。

示例 1：

输入：nums = [2,4,-2], k = 5
输出：2
解释：所有可能获得的子序列和列出如下，按递减顺序排列：
6、4、4、2、2、0、0、-2
数组的第 5 大和是 2 。

示例 2：

输入：nums = [1,-2,3,4,-10,12], k = 16
输出：10
解释：数组的第 16 大和是 10 。

提示：

n == nums.length
1 <= n <= 105
-109 <= nums[i] <= 109
1 <= k <= min(2000, 2n)
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

using namespace std;

class Solution {
   public:
    long long kSum(vector<int>& nums, int k) {
        // 最大和
        long sum = 0L;
        for (int& x : nums) {
            if (x >= 0) {
                sum += x;
            } else {
                x = -x;
            }
        }
        ranges::sort(nums);

        // 要减去的最小正数，或要加上的最大负数，小顶堆
        priority_queue<pair<long, int>, vector<pair<long, int>>, greater<>> pq;
        pq.emplace(0, 0);  // 空子序列
        while (--k) {
            auto [s, i] = pq.top();
            pq.pop();
            if (i < nums.size()) {
                // 在子序列的末尾添加 nums[i]
                pq.emplace(s + nums[i],
                           i + 1);  // 下一个添加/替换的元素下标为 i+1
                if (i) {            // 替换子序列的末尾元素为 nums[i]
                    pq.emplace(s + nums[i] - nums[i - 1], i + 1);
                }
            }
        }
        // 取第k小的绝对值数
        return sum - pq.top().first;
    }
};

int main() {
    Solution s;
    vector<int> nums = {2, 4, -2};
    int k = 5;
    cout << s.kSum(nums, k) << endl;

    nums = {1, -2, 3, 4, -10, 12};
    k = 16;
    cout << s.kSum(nums, k) << endl;
    return 0;
}

// g++ 20240309.cpp -std=c++20