/*
2552. 统计上升四元组

给你一个长度为 n 下标从 0 开始的整数数组 nums ，它包含 1 到 n 的所有数字，请你返回上升四元组的数目。

如果一个四元组 (i, j, k, l) 满足以下条件，我们称它是上升的：

0 <= i < j < k < l < n 且
nums[i] < nums[k] < nums[j] < nums[l] 。


示例 1：

输入：nums = [1,3,2,4,5]
输出：2
解释：
- 当 i = 0 ，j = 1 ，k = 2 且 l = 3 时，有 nums[i] < nums[k] < nums[j] < nums[l] 。
- 当 i = 0 ，j = 1 ，k = 2 且 l = 4 时，有 nums[i] < nums[k] < nums[j] < nums[l] 。
没有其他的四元组，所以我们返回 2 。


示例 2：

输入：nums = [1,2,3,4]
输出：0
解释：只存在一个四元组 i = 0 ，j = 1 ，k = 2 ，l = 3 ，但是 nums[j] < nums[k] ，所以我们返回 0 。
 

提示：

4 <= nums.length <= 4000
1 <= nums[i] <= nums.length
nums 中所有数字 互不相同 ，nums 是一个排列。
*/


// 思路：枚举 j 和 k，然后统计比 nums[j] 小的数的个数和比 nums[k] 大的数的个数，然后相乘即可
// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> great(n, vector<int>(n+1));
        for(int k = n-2; k >= 2; k--){
            great[k] = great[k+1];
            for(int x=1; x<nums[k+1]; x++){ // 比 nums[k+1] 小的数，都要 +1
                great[k][x]++;
            }
        }

        long long ans = 0;
        vector<int> less(n+1);
        for(int j = 1; j < n-2; j++){
            for(int x = nums[j-1] + 1; x <= n; x++){ // 比 nums[j-1] 大的数，都要 +1
                less[x]++;
            }
            for(int k = j+1; k < n-1; k++){
                if(nums[j] > nums[k]){
                    ans += less[nums[k]] * great[k][nums[j]];
                }
            }
        }

        return ans;
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,3,2,4,5};
    cout << s.countQuadruplets(nums) << endl;

    nums = {1,2,3,4};
    cout << s.countQuadruplets(nums) << endl;
    return 0;
}