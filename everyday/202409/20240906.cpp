/*
3176. 求出最长好子序列 I

给你一个整数数组 nums 和一个 非负 整数 k 。如果一个整数序列 seq 满足在下标范围 [0, seq.length - 2] 中 最多只有 k 个下标 i 满足 seq[i] != seq[i + 1] ，那么我们称这个整数序列为 好 序列。

请你返回 nums 中 好 子序列  的最长长度。

子序列 是可以通过从另一个数组删除或不删除某些元素，但不更改其余元素的顺序得到的数组。



示例 1：

输入：nums = [1,2,1,1,3], k = 2

输出：4

解释：

最长好子序列为 [1,2,1,1], [2,1,1,3], [1,1,1,3]

其中只有 2 个下标满足 seq[i] != seq[i + 1] 。




示例 2：

输入：nums = [1,2,3,4,5,1], k = 0

输出：2

解释：

最长好子序列为 [1,2,3,4,5,1] 。



提示：

1 <= nums.length <= 500
1 <= nums[i] <= 109
0 <= k <= min(nums.length, 25)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        // dp[i][j]: 以nums[i]结尾，相邻数字不同的对数不超过j的 最长子序列长度
        vector<vector<int>> dp(n, vector<int>(k+1, 1));
        int ans = dp[0][k];
        for(int i = 1; i < n; i++){
            for(int j = 0; j <= k; j++){
                for(int t = i - 1; t > -1; t--){
                    if(nums[t] == nums[i]){
                        dp[i][j] = max(dp[i][j], dp[t][j] + 1);
                    }else{
                        if(j>0) dp[i][j] = max(dp[i][j], dp[t][j-1] + 1);
                    }
                }
            }
            ans = max(ans, dp[i][k]);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    vector<int> nums = {1,2,1,1,3};
    int k = 2;
    cout << s.maximumLength(nums, k) << endl;

    nums = {1,2,3,4,5,1};
    k = 0;
    cout << s.maximumLength(nums, k) << endl;

    return 0;
}