/*
3264. K 次乘运算后的最终数组 I

给你一个整数数组 nums ，一个整数 k  和一个整数 multiplier 。

你需要对 nums 执行 k 次操作，每次操作中：

找到 nums 中的 最小 值 x ，如果存在多个最小值，选择最 前面 的一个。

将 x 替换为 x * multiplier 。

请你返回执行完 k 次乘运算之后，最终的 nums 数组。



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



示例 2：

输入：nums = [1,2], k = 3, multiplier = 4

输出：[16,8]

解释：

操作	结果
1 次操作后	[4, 2]
2 次操作后	[4, 8]
3 次操作后	[16, 8]
 

提示：

1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 10
1 <= multiplier <= 5
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <queue>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        // 使用 views::enumerate 将 nums 转换成带索引的视图，每个元素变成 (index, value) 的形式
        // 使用 views::transform 转换视图，将每个 (index, value) 对变为 (value, index) 的形式。
        // 将视图转换为优先队列（priority_queue），使用 greater{} 实现最小堆，即值较小的元素优先出队。
        // auto pq = nums | views::enumerate 
        //                | views::transform([](auto p) { return pair{get<1>(p), get<0>(p)}; })
        //                | ranges::to<priority_queue>(greater{});

        // 定义一个优先队列，存储 (value, index) 对，使用最小堆
        using Element = pair<int, int>;
        priority_queue<Element, vector<Element>, greater<Element>> pq;
        // 初始化优先队列
        for (int i = 0; i < nums.size(); ++i) {
            pq.emplace(nums[i], i);
        }

        for (;k--; pq.pop()) {
            auto [v, i] = pq.top();
            // 更新原数组 nums[i] 的值为 v * multiplier。
            // 将更新后的 (new_value, i) 再次插入优先队列。
            pq.emplace(nums[i] = v * multiplier, i);
        }
        return nums;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {2,1,3,5,6};
    int k = 5, multiplier = 2;
    auto result = solution.getFinalState(nums, k, multiplier);
    for (auto &num : result) {
        cout << num << " ";
    }
    cout << endl;

    nums = {1,2};
    k = 3, multiplier = 4;
    result = solution.getFinalState(nums, k, multiplier);
    for (auto &num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
