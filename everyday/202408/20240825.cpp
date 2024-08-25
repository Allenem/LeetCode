/*
698. 划分为k个相等的子集

给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。


示例 1：

输入： nums = [4, 3, 2, 3, 5, 2, 1], k = 4
输出： True
说明： 有可能将其分成 4 个子集（5），（1,4），（2,3），（2,3）等于总和。


示例 2:

输入: nums = [1,2,3,4], k = 3
输出: false


提示：

1 <= k <= len(nums) <= 16
0 < nums[i] < 10000
每个元素的频率在 [1,4] 范围内
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool bk(vector<int>& nums, vector<int>& buckets, int k, int idx) {
        if(idx >= nums.size()) return true;                   // 如果把数字都分完了
        for(int i=0; i<k; i++){
            if(nums[idx] > buckets[i]) continue;              // 当前桶 buckets[i] 放不下 nums[idx] 的量
            if(i > 0 && buckets[i] == buckets[i-1]) continue; // 剪枝
            buckets[i] -= nums[idx];
            if(bk(nums, buckets, k, idx+1)) return true;
            buckets[i] += nums[idx];                          // 回溯，因为有可能放错
        }
        return false;
    }

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k) return false;
        int tgt = sum / k;
        vector<int> buckets(k, tgt);
        sort(nums.rbegin(),nums.rend());                     // 从大到小放数字
        return bk(nums, buckets, k, 0);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    int k = 4;
    cout << boolalpha;
    cout << sol.canPartitionKSubsets(nums, k) << endl;

    nums = {1,2,3,4};
    k = 3;
    cout << sol.canPartitionKSubsets(nums, k) << endl;

    return 0;
}