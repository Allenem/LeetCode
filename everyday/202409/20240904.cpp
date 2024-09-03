/*
2860. 让所有学生保持开心的分组方法数

给你一个下标从 0 开始、长度为 n 的整数数组 nums ，其中 n 是班级中学生的总数。班主任希望能够在让所有学生保持开心的情况下选出一组学生：

如果能够满足下述两个条件之一，则认为第 i 位学生将会保持开心：

- 这位学生被选中，并且被选中的学生人数 严格大于 nums[i] 。
- 这位学生没有被选中，并且被选中的学生人数 严格小于 nums[i] 。

返回能够满足让所有学生保持开心的分组方法的数目。


示例 1：

输入：nums = [1,1]
输出：2
解释：
有两种可行的方法：
班主任没有选中学生。
班主任选中所有学生形成一组。 
如果班主任仅选中一个学生来完成分组，那么两个学生都无法保持开心。因此，仅存在两种可行的方法。


示例 2：

输入：nums = [6,0,3,3,6,7,2,7]
输出：3
解释：
存在三种可行的方法：
班主任选中下标为 1 的学生形成一组。
班主任选中下标为 1、2、3、6 的学生形成一组。
班主任选中所有学生形成一组。 


提示：

1 <= nums.length <= 105
0 <= nums[i] < nums.length
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countWays(vector<int> &nums) {
        // 排序+枚举：首先对数组排序，设选出的学生的元素集合为 {x_i}，未选的学生的元素集合为 {y_i}，则有 max{x_i}<∣{x_i}∣<min{y_i}，
        // 所有若存在选择方案，则选出学生一定是数组的一个前缀，且未选的学生是数组剩余的后缀，枚举可能的前后缀划分情况。
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        if (nums[n - 1] < n)//后缀为空
            res++;
        if (nums[0] > 0)//前缀为空
            res++;
        for (int i = 0; i < n - 1; i++) {//枚举前缀nums[0,i]
            if (nums[i] < i + 1 && nums[i + 1] > i + 1)
                res++;
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 1};
    cout << sol.countWays(nums) << endl;
    nums = {6, 0, 3, 3, 6, 7, 2, 7};
    cout << sol.countWays(nums) << endl;
    return 0;
}