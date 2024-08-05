/*
600. 不含连续1的非负整数

给定一个正整数 n ，请你统计在 [0, n] 范围的非负整数中，有多少个整数的二进制表示中不存在 连续的 1 。


示例 1:

输入: n = 5
输出: 5
解释: 
下面列出范围在 [0, 5] 的非负整数与其对应的二进制表示：
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
其中，只有整数 3 违反规则（有两个连续的 1 ），其他 5 个满足规则。


示例 2:

输入: n = 1
输出: 2


示例 3:

输入: n = 2
输出: 3
 

提示:

1 <= n <= 10^9
*/
#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int findIntegers(int n) {
        if(n==0) return 1;

        int m; // 二进制数n的长度：m
        for(m=31; m>-1; m--){ // 从左到右遍历
            if(((n>>m)&1)==1){
                m++;
                break;
            }
        }

        // dp[i][0]:长度为i+1，最高位为0的不含连续1的个数
        // dp[i][1]:长度为i+1，最高位为1的不含连续1的个数 
        vector<vector<int>>dp(m, vector<int>{0, 1});
        dp[0][0] = 1;
        for(int i=1; i<m; i++){ // 从右到左遍历
            dp[i][0] = dp[i-1][0] + dp[i-1][1];
            dp[i][1] = dp[i-1][0];
        }

        int ans=0, pre=0, cur;
        for(int i=m-1; i>-1; i--){ // 从左到右遍历
            // 当前位是 0 还是 1
            cur = (((n>>i)&1)==1);

            // 第i位替换成0，才能不连续1
            if(cur==1) ans += dp[i][0];

            // 判断当前是否出现连续为1，出现则结束for
            if(cur==1&&pre==1) break;

            // 容易被遗忘的边界，即判断n是否含有连续1
            if(i==0) ans++;

            pre = cur;
        }

        return ans;
    }
};

int main(){
    Solution s;
    cout<<s.findIntegers(5)<<endl; // 5
    cout<<s.findIntegers(1)<<endl; // 2
    cout<<s.findIntegers(2)<<endl; // 3
    return 0;
}