/*
503. 下一个更大元素 II

给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的 下一个更大元素 。

数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。

示例 1:

输入: nums = [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

示例 2:

输入: nums = [1,2,3,4,3]
输出: [2,3,4,-1,4]

提示:

1 <= nums.length <= 104
-109 <= nums[i] <= 109
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 暴力解法
class Solution1 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        nums.insert(nums.end(), nums.begin(), nums.end());
        for (int i = 0;i < n;i++) {
            for (int j = i + 1;j < 2 * n;j++) {
                if (nums[j] > nums[i]) {
                    ans[i] = nums[j];
                    break;
                }
            }
        }
        return ans;
    }
};

// 单调栈
class Solution2 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> stk;
        for (int i = 0;i < 2 * n;i++) {
            while (!stk.empty() && nums[stk.top()] < nums[i % n]) {
                ans[stk.top()] = nums[i % n];
                stk.pop();
            }
            stk.push(i % n);
        }
        return ans;
    }
};

int main() {
    Solution1 s1;
    Solution2 s2;
    for (auto nums : vector<vector<int>>{ {1,2,1},{1,2,3,4,3} }) {
        for (auto num : s2.nextGreaterElements(nums)) {
            cout << num << " ";
        }
        cout << endl;
        // 暴力解法，放后面因为会复制一份 nums
        for (auto num : s1.nextGreaterElements(nums)) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}