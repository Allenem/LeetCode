/*
3232. 判断是否可以赢得数字游戏

给你一个 正整数 数组 nums。

Alice 和 Bob 正在玩游戏。在游戏中，Alice 可以从 nums 中选择所有个位数 或 所有两位数，剩余的数字归 Bob 所有。如果 Alice 所选数字之和 严格大于 Bob 的数字之和，则 Alice 获胜。

如果 Alice 能赢得这场游戏，返回 true；否则，返回 false。

 

示例 1：

输入：nums = [1,2,3,4,10]

输出：false

解释：

Alice 不管选个位数还是两位数都无法赢得比赛。



示例 2：

输入：nums = [1,2,3,4,5,14]

输出：true

解释：

Alice 选择个位数可以赢得比赛，所选数字之和为 15。



示例 3：

输入：nums = [5,5,5,25]

输出：true

解释：

Alice 选择两位数可以赢得比赛，所选数字之和为 25。

 

提示：

1 <= nums.length <= 100
1 <= nums[i] <= 99
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canAliceWin(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int allsum = accumulate(nums.begin(), nums.end(), 0), half = 0;
        for(int numi:nums){
            if(numi>9) break;
            half+=numi;
        }
        return half*2 == allsum ? false : true;
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,2,3,4,10};
    cout << boolalpha;
    cout << s.canAliceWin(nums) << endl;

    nums = {1,2,3,4,5,14};
    cout << s.canAliceWin(nums) << endl;

    nums = {5,5,5,25};
    cout << s.canAliceWin(nums) << endl;
    return 0;
}