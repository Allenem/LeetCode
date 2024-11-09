/*
540. 有序数组中的单一元素

给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。

请你找出并返回只出现一次的那个数。

你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。



示例 1:

输入: nums = [1,1,2,3,3,4,4,8,8]
输出: 2



示例 2:

输入: nums =  [3,3,7,7,10,11,11]
输出: 10
 


提示:

1 <= nums.length <= 105
0 <= nums[i] <= 105
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        // 二分查找，如果中间 偶数=奇数 索引，说明左边都重复了，所求在右半部分
        int l = 0, r = nums.size() - 1;
        while(l < r){
            int mid = (l + r) / 2;
            // 这里两方面来理解：
            // mid 奇数，mid^1 = mid-1. if nums[mid-1] = nums[mid] 所求在右
            // mid 偶数，mid^1 = mid+1. if nums[mid] = nums[mid+1] 所求在右
            if(nums[mid] == nums[mid ^ 1]){
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return nums[r];
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,1,2,3,3,4,4,8,8};
    cout << s.singleNonDuplicate(nums) << endl;

    nums = {3,3,7,7,10,11,11};
    cout << s.singleNonDuplicate(nums) << endl;
    return 0;
}