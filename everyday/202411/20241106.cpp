/*
3254. 长度为 K 的子数组的能量值 I

给你一个长度为 n 的整数数组 nums 和一个正整数 k 。

一个数组的 能量值 定义为：

如果 所有 元素都是依次 连续 且 上升 的，那么能量值为 最大 的元素。否则为 -1 。

你需要求出 nums 中所有长度为 k 的 子数组 的能量值。

请你返回一个长度为 n - k + 1 的整数数组 results ，其中 results[i] 是子数组 nums[i..(i + k - 1)] 的能量值。



示例 1：

输入：nums = [1,2,3,4,3,2,5], k = 3

输出：[3,4,-1,-1,-1]

解释：

nums 中总共有 5 个长度为 3 的子数组：

[1, 2, 3] 中最大元素为 3 。
[2, 3, 4] 中最大元素为 4 。
[3, 4, 3] 中元素 不是 连续的。
[4, 3, 2] 中元素 不是 上升的。
[3, 2, 5] 中元素 不是 连续的。



示例 2：

输入：nums = [2,2,2,2,2], k = 4

输出：[-1,-1]



示例 3：

输入：nums = [3,2,3,2,3,2], k = 2

输出：[-1,3,-1,3,-1]

 

提示：

1 <= n == nums.length <= 500
1 <= nums[i] <= 105
1 <= k <= n
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n-k+1, -1);
        for(int i=0, cnt=1; i<n; i++){
            if(i>0 && nums[i]==nums[i-1]+1) cnt++;
            else cnt=1;
            if(cnt>=k) ans[i-k+1]=nums[i]; // 统计连续上升 >= k 的就行
        }
        return ans;
    }
};

int main(){
    Solution s;

    vector<int> nums = {1,2,3,4,3,2,5};
    int k = 3;
    vector<int> ans = s.resultsArray(nums, k);
    for(auto x: ans) cout << x << " ";
    cout << endl;

    nums = {2,2,2,2,2};
    k = 4;
    ans = s.resultsArray(nums, k);
    for(auto x: ans) cout << x << " ";
    cout << endl;

    nums = {3,2,3,2,3,2};
    k = 2;
    ans = s.resultsArray(nums, k);
    for(auto x: ans) cout << x << " ";
    cout << endl;

    return 0;
}