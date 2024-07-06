/*
3101. 交替子数组计数

给你一个二进制数组 nums 。

如果一个 子数组 中 不存在 两个 相邻 元素的值 相同 的情况，我们称这样的子数组为 交替子数组 。

返回数组 nums 中交替子数组的数量。

示例 1：

输入： nums = [0,1,1,1]

输出： 5

解释：

以下子数组是交替子数组：[0] 、[1] 、[1] 、[1] 以及 [0,1] 。

示例 2：

输入： nums = [1,0,1,0]

输出： 10

解释：

数组的每个子数组都是交替子数组。可以统计在内的子数组共有 10 个。 

提示：

1 <= nums.length <= 105
nums[i] 不是 0 就是 1 。
*/
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long ans=0,curlen=0;
        int prenum=-1;
        for(int a:nums){
            curlen=(a==prenum)?1:curlen+1;
            prenum=a;
            ans+=curlen;
        }
        return ans;
    }
};
int main(){
    Solution s;
    for(auto a:{vector<int>({0,1,1,1}),vector<int>({1,0,1,0})}){
        cout<<s.countAlternatingSubarrays(a)<<endl;
    }
    return 0;
}