/*
2848. 与车相交的点

给你一个下标从 0 开始的二维整数数组 nums 表示汽车停放在数轴上的坐标。对于任意下标 i，nums[i] = [starti, endi] ，其中 starti 是第 i 辆车的起点，endi 是第 i 辆车的终点。

返回数轴上被车 任意部分 覆盖的整数点的数目。

 

示例 1：

输入：nums = [[3,6],[1,5],[4,7]]
输出：7
解释：从 1 到 7 的所有点都至少与一辆车相交，因此答案为 7 。


示例 2：

输入：nums = [[1,3],[5,8]]
输出：7
解释：1、2、3、5、6、7、8 共计 7 个点满足至少与一辆车相交，因此答案为 7 。
 

提示：

1 <= nums.length <= 100
nums[i].length == 2
1 <= starti <= endi <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int ans=0, n=nums.size();
        if(n==1)return nums[0][1]-nums[0][0]+1;
        sort(nums.begin(), nums.end());
        for(int i=1;i<n;i++){
            if(nums[i-1][1]<nums[i][0])ans+=nums[i-1][1]-nums[i-1][0]+1;
            else nums[i][0]=min(nums[i-1][0],nums[i][0]), nums[i][1]=max(nums[i-1][1],nums[i][1]);
            if(i==n-1) ans+=nums[i][1]-nums[i][0]+1;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> nums = {{3,6},{1,5},{4,7}};
    cout << sol.numberOfPoints(nums) << endl;

    nums = {{1,3},{5,8}};
    cout << sol.numberOfPoints(nums) << endl;
    return 0;
}