/*
1017. 负二进制转换

给你一个整数 n ，以二进制字符串的形式返回该整数的 负二进制（base -2）表示。

注意，除非字符串就是 "0"，否则返回的字符串中不能含有前导零。

示例 1：

输入：n = 2
输出："110"
解释：(-2)^2 + (-2)^1 = 2

示例 2：

输入：n = 3
输出："111"
解释：(-2)^2 + (-2)^1 + (-2)^0 = 3
示例 3：

输入：n = 4
输出："100"
解释：(-2)^2 = 4
 

提示：

0 <= n <= 10^9
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string baseNeg2(int n) {
        if(n==0) return (string) "0";
        string ans="";
        while(n){
            int mod=abs(n%(-2));
            ans=(mod==0)?("0"+ans):("1"+ans);
            n=(n-mod)/(-2);
        }
        return ans;
    }
};

int main() {
    Solution solution;
    cout << solution.baseNeg2(0) << endl;
    cout << solution.baseNeg2(1) << endl;
    cout << solution.baseNeg2(2) << endl;
    cout << solution.baseNeg2(3) << endl;
    cout << solution.baseNeg2(4) << endl;
    cout << solution.baseNeg2(5) << endl;
    cout << solution.baseNeg2(6) << endl;
    cout << solution.baseNeg2(1e9) << endl;
    return 0;
}