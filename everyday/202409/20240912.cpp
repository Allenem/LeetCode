/*
2576. 求出最多标记下标

给你一个下标从 0 开始的整数数组 nums 。

一开始，所有下标都没有被标记。你可以执行以下操作任意次：

选择两个 互不相同且未标记 的下标 i 和 j ，满足 2 * nums[i] <= nums[j] ，标记下标 i 和 j 。

请你执行上述操作任意次，返回 nums 中最多可以标记的下标数目。



示例 1：

输入：nums = [3,5,2,4]
输出：2
解释：第一次操作中，选择 i = 2 和 j = 1 ，操作可以执行的原因是 2 * nums[2] <= nums[1] ，标记下标 2 和 1 。
没有其他更多可执行的操作，所以答案为 2 。



示例 2：

输入：nums = [9,2,5,4]
输出：4
解释：第一次操作中，选择 i = 3 和 j = 0 ，操作可以执行的原因是 2 * nums[3] <= nums[0] ，标记下标 3 和 0 。
第二次操作中，选择 i = 1 和 j = 2 ，操作可以执行的原因是 2 * nums[1] <= nums[2] ，标记下标 1 和 2 。
没有其他更多可执行的操作，所以答案为 4 。



示例 3：

输入：nums = [7,6,8]
输出：0
解释：没有任何可以执行的操作，所以答案为 0 。



提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        // ranges::sort(nums);
        sort(nums.begin(), nums.end());

        auto check = [&](int k) -> bool {
            for (int i = 0; i < k; i++) {
                if (nums[i] * 2 > nums[nums.size() - k + i]) {
                    return false;
                }
            }
            return true;
        };

        int left = 0, right = nums.size() / 2 + 1; // 开区间
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left * 2; // 最多匹配 left 对，有 left * 2 个数
    }
};

int main() {
    vector<vector<int>> numsList = {
        {3, 5, 2, 4},
        {9, 2, 5, 4},
        {7, 6, 8}
    }; // 预期结果分别是 2, 4, 0
    for (auto &nums : numsList) {
        cout << Solution().maxNumOfMarkedIndices(nums) << endl;
    }
    return 0;
}