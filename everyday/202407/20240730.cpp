/*
2961. 双模幂运算

给你一个下标从 0 开始的二维数组 variables ，其中 variables[i] = [ai, bi, ci, mi]，以及一个整数 target 。

如果满足以下公式，则下标 i 是 好下标：

0 <= i < variables.length

((aibi % 10)ci) % mi == target

返回一个由 好下标 组成的数组，顺序不限 。

示例 1：

输入：variables = [[2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
输出：[0,2]
解释：对于 variables 数组中的每个下标 i ：
1) 对于下标 0 ，variables[0] = [2,3,3,10] ，(23 % 10)3 % 10 = 2 。
2) 对于下标 1 ，variables[1] = [3,3,3,1] ，(33 % 10)3 % 1 = 0 。
3) 对于下标 2 ，variables[2] = [6,1,1,4] ，(61 % 10)1 % 4 = 2 。
因此，返回 [0,2] 作为答案。

示例 2：

输入：variables = [[39,3,1000,1000]], target = 17
输出：[]
解释：对于 variables 数组中的每个下标 i ：
1) 对于下标 0 ，variables[0] = [39,3,1000,1000] ，(393 % 10)1000 % 1000 = 1 。
因此，返回 [] 作为答案。

提示：

1 <= variables.length <= 100
variables[i] == [ai, bi, ci, mi]
1 <= ai, bi, ci, mi <= 10^3
0 <= target <= 10^3
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int fpow(int x, int n, int mod){
        int res=1;
        for(int e=x;n;e=e*e%mod,n>>=1)
            if(n&1)res=res*e%mod;
        return res;
    }
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        vector<int>ans;
        for(int i=0;i<variables.size();i++)
            if(fpow(fpow(variables[i][0],variables[i][1],10),variables[i][2],variables[i][3])==target)
                ans.push_back(i);
        return ans;
    }
};

int main(){
    Solution s;
    
    vector<vector<int>> variables = {{2,3,3,10},{3,3,3,1},{6,1,1,4}};
    int target = 2;
    vector<int> ans = s.getGoodIndices(variables, target);
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";
    cout<<endl;

    vector<vector<int>> variables2 = {{39,3,1000,1000}};
    int target2 = 17;
    vector<int> ans2 = s.getGoodIndices(variables2, target2);
    for(int i=0;i<ans2.size();i++)
        cout<<ans2[i]<<" ";
    cout<<endl;

    return 0;
}