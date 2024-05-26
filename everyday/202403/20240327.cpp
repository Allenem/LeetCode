/*
2580. 统计将重叠区间合并成组的方案数

给你一个二维整数数组 ranges ，其中 ranges[i] = [starti, endi] 表示 starti 到
endi 之间（包括二者）的所有整数都包含在第 i 个区间中。

你需要将 ranges 分成 两个 组（可以为空），满足：

每个区间只属于一个组。
两个有 交集 的区间必须在 同一个 组内。
如果两个区间有至少 一个 公共整数，那么这两个区间是 有交集 的。

比方说，区间 [1, 3] 和 [2, 5] 有交集，因为 2 和 3 在两个区间中都被包含。
请你返回将 ranges 划分成两个组的 总方案数 。由于答案可能很大，将它对 109 + 7
取余 后返回。

示例 1：

输入：ranges = [[6,10],[5,15]]
输出：2
解释：
两个区间有交集，所以它们必须在同一个组内。
所以有两种方案：
- 将两个区间都放在第 1 个组中。
- 将两个区间都放在第 2 个组中。

示例 2：

输入：ranges = [[1,3],[10,20],[2,5],[4,8]]
输出：4
解释：
区间 [1,3] 和 [2,5] 有交集，所以它们必须在同一个组中。
同理，区间 [2,5] 和 [4,8] 也有交集，所以它们也必须在同一个组中。
所以总共有 4 种分组方案：
- 所有区间都在第 1 组。
- 所有区间都在第 2 组。
- 区间 [1,3] ，[2,5] 和 [4,8] 在第 1 个组中，[10,20] 在第 2 个组中。
- 区间 [1,3] ，[2,5] 和 [4,8] 在第 2 个组中，[10,20] 在第 1 个组中。

提示：

1 <= ranges.length <= 105
ranges[i].length == 2
0 <= starti <= endi <= 109
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countWays(vector<vector<int>>& ranges) {
        ranges::sort(ranges, [](auto& a, auto& b) { return a[0] < b[0]; });
        int ans = 1, max_r = -1;
        for (auto& p : ranges) {
            if (p[0] > max_r) {                 // 无法合并
                ans = ans * 2 % 1'000'000'007;  // 新区间
            }
            max_r = max(max_r, p[1]);  // 合并
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> ranges1 = {{6, 10}, {5, 15}};
    cout << sol.countWays(ranges1) << endl;
    vector<vector<int>> ranges2 = {{1, 3}, {10, 20}, {2, 5}, {4, 8}};
    cout << sol.countWays(ranges2) << endl;
    return 0;
}

// g++ 20240327.cpp -std=c++20