/*
3250. 单调数组对的数目 I

给你一个长度为 n 的 正 整数数组 nums 。

如果两个 非负 整数数组 (arr1, arr2) 满足以下条件，我们称它们是 单调 数组对：

两个数组的长度都是 n 。
arr1 是单调 非递减 的，换句话说 arr1[0] <= arr1[1] <= ... <= arr1[n - 1] 。
arr2 是单调 非递增 的，换句话说 arr2[0] >= arr2[1] >= ... >= arr2[n - 1] 。
对于所有的 0 <= i <= n - 1 都有 arr1[i] + arr2[i] == nums[i] 。
请你返回所有 单调 数组对的数目。

由于答案可能很大，请你将它对 109 + 7 取余 后返回。



示例 1：

输入：nums = [2,3,2]

输出：4

解释：

单调数组对包括：

([0, 1, 1], [2, 2, 1])
([0, 1, 2], [2, 2, 0])
([0, 2, 2], [2, 1, 0])
([1, 2, 2], [1, 1, 0])



示例 2：

输入：nums = [5,5,5,5]

输出：126

 

提示：

1 <= n == nums.length <= 2000
1 <= nums[i] <= 50
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countOfPairs0(vector<int>& nums) {
        int n = nums.size(), mod = 1e9 + 7;
        vector<vector<int>> dp(n, vector<int>(51, 0));
        for(int v = 0; v <= nums[0]; v++) dp[0][v] = 1;

        for(int i = 1; i < n; i++){
            for(int v2 = 0; v2 <= nums[i]; v2++){
                for(int v1 = 0; v1 <= v2; v1++){
                    if(nums[i-1] - v1 >= nums[i] - v2){
                        dp[i][v2] = (dp[i][v2] + dp[i-1][v1]) % mod;
                    }
                }
            }
        }

        int res = 0;
        for(int v : dp[n-1]) res = (res + v) % mod;
        return res;
    }

    int countOfPairs1(vector<int>& nums) {
        int n = nums.size(), mod = 1e9 + 7, m = ranges::max(nums);
        vector<vector<int>> dp(n, vector<int>(m+1, 0)); // dp[i][j] 表示当 arr1[i]=j 时，前 i+1 个元素组成的单调数组的数目。
        for(int v = 0; v <= nums[0]; v++) dp[0][v] = 1;

        for(int i = 1; i < n; i++){
            int k = max(0, nums[i] - nums[i-1]);
            for(int j = k; j <= nums[i]; j++){
                dp[i][j] = j==0 ? dp[i-1][j-k] : (dp[i][j-1] + dp[i-1][j-k])%mod;
            }
        }

        int res = 0;
        for(int v : dp[n-1]) res = (res + v) % mod;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> nums = {2,3,2};
    cout << s.countOfPairs0(nums) << endl;
    cout << s.countOfPairs1(nums) << endl;

    nums = {5,5,5,5};
    cout << s.countOfPairs0(nums) << endl;
    cout << s.countOfPairs1(nums) << endl;
    
    return 0;
}//g++ 20241128.cpp -std=c++20