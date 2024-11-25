/*
632. 最小区间

你有 k 个 非递减排列 的整数列表。找到一个 最小 区间，使得 k 个列表中的每个列表至少有一个数包含在其中。

我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。

 

示例 1：

输入：nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
输出：[20,24]
解释： 
列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。



示例 2：

输入：nums = [[1,2,3],[1,2,3],[1,2,3]]
输出：[1,1]
 

提示：

nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-105 <= nums[i][j] <= 105
nums[i] 按非递减顺序排列
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int rangeLeft = 0, rangeRight = INT_MAX;
        int size = nums.size();
        vector<int> next(size);
        
        auto cmp = [&](const int& u, const int& v) {
            return nums[u][next[u]] > nums[v][next[v]];
        };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        int minValue = 0, maxValue = INT_MIN;
        for (int i = 0; i < size; ++i) {
            pq.emplace(i);
            maxValue = max(maxValue, nums[i][0]);
        }

        while (true) {
            int row = pq.top();
            pq.pop();
            minValue = nums[row][next[row]];
            if (maxValue - minValue < rangeRight - rangeLeft) {
                rangeLeft = minValue;
                rangeRight = maxValue;
            }
            if (next[row] == nums[row].size() - 1) {
                break;
            }
            ++next[row];
            maxValue = max(maxValue, nums[row][next[row]]);
            pq.emplace(row);
        }

        return {rangeLeft, rangeRight};
    }
};

// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/smallest-range-covering-elements-from-k-lists/solutions/355881/zui-xiao-qu-jian-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution sol;
    vector<vector<int>> nums = {{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}};
    vector<int> result = sol.smallestRange(nums);
    cout << result[0] << " " << result[1] << endl;

    nums = {{1,2,3},{1,2,3},{1,2,3}};
    result = sol.smallestRange(nums);
    cout << result[0] << " " << result[1] << endl;
    return 0;
}