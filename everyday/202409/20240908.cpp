/*
977. 有序数组的平方

给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。


示例 1：

输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]


示例 2：

输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
 

提示：

1 <= nums.length <= 10^4
-104 <= nums[i] <= 10^4
nums 已按 非递减顺序 排序
 

进阶：

请你设计时间复杂度为 O(n) 的算法解决本问题
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int>ans;
        for(auto num:nums)ans.push_back(pow(num,2));
        // ranges::sort(ans);
        sort(ans.begin(),ans.end());
        return ans;
    }
};

int main(){
    Solution s;
    vector<int>nums = {-4,-1,0,3,10};
    vector<int>ans = s.sortedSquares(nums);
    for(auto num:ans)cout<<num<<' ';
    cout<<endl;

    nums = {-7,-3,2,3,11};
    ans = s.sortedSquares(nums);
    for(auto num:ans)cout<<num<<' ';
    cout<<endl;

    return 0;
}