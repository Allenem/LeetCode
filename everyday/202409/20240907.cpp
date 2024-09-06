/*
3177. 求出最长好子序列 II

给你一个整数数组 nums 和一个 非负 整数 k 。如果一个整数序列 seq 满足在范围下标范围 [0, seq.length - 2] 中存在 不超过 k 个下标 i 满足 seq[i] != seq[i + 1] ，那么我们称这个整数序列为 好 序列。

请你返回 nums 中 好 子序列 的最长长度。子序列 是可以通过从另一个数组删除或不删除某些元素，但不更改其余元素的顺序得到的数组。

 

示例 1：

输入：nums = [1,2,1,1,3], k = 2

输出：4

解释：

最长好子序列为 [1,2,1,1,3] 。
               v v v v


示例 2：

输入：nums = [1,2,3,4,5,1], k = 0

输出：2

解释：

最长好子序列为 [1,2,3,4,5,1] 。
               v         v

 

提示：

1 <= nums.length <= 5 * 10^3
1 <= nums[i] <= 109
0 <= k <= min(50, nums.length)
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size(), ans = 1;

        // dp[i][j] 表示以第i个数字结尾的允许最大下标不满足数为j个的好子序列的最大长度
        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));

        // 优化O（n）查询最值的时间，通过一个数组来保存上一次循环中（即最大允许j-1个不同值）的到i位置上（可能以i结尾，也可能不是）的最大值长度
        vector<int> mx(n+1, 0);

        for(int j=0; j<=k; j++){
            // hash[nums[i-1]]表示以nums[i-1]结尾的好子序列的最大值（相同的j，且在i之前）
            unordered_map<int, int> hash;
            vector<int> tmp = mx;
            for(int i=1; i<=n; i++){
                if(j==0) dp[i][j] = 1;
                else dp[i][j] = dp[i][j-1];
                dp[i][j] = max(dp[i][j], max(tmp[i-1], hash[nums[i-1]]) + 1);
                hash[nums[i-1]] = max(hash[nums[i-1]], dp[i][j]);
                mx[i] = max(mx[i-1], dp[i][j]);
                ans = max(ans, dp[i][j]);
            }
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