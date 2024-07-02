/*
3115. 质数的最大距离

给你一个整数数组 nums。

返回两个（不一定不同的）质数在 nums 中 下标 的 最大距离。

示例 1：

输入： nums = [4,2,9,5,3]

输出： 3

解释： nums[1]、nums[3] 和 nums[4] 是质数。因此答案是 |4 - 1| = 3。

示例 2：

输入： nums = [4,8,2,8]

输出： 0

解释： nums[2] 是质数。因为只有一个质数，所以答案是 |2 - 2| = 0。

提示：

1 <= nums.length <= 3 * 105
1 <= nums[i] <= 100
输入保证 nums 中至少有一个质数。
*/
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        auto isp=[](int x)->bool{
            if(x<=3) return x>1;
            int sqrt_=(int)sqrt(x);
            for(int i=2;i<=sqrt_;i++){
                if(x%i==0) return false;
            }
            return true;
        };
        int first=-1,flag=0,n=nums.size(),ans=0;
        for(int i=0;i<n;i++){
            if(isp(nums[i])){
                if(!flag) {
                    first=i;
                    flag=1;
                }else {
                    ans=i-first;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    for (vector<int> nums: vector<vector<int>>{{4,2,9,5,3}, {4,8,2,8}}) {
        cout << sol.maximumPrimeDifference(nums) << endl;
    }
    return 0;
}