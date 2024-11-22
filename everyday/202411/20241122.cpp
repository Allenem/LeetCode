/*
3233. 统计不是特殊数字的数字数量

给你两个 正整数 l 和 r。对于任何数字 x，x 的所有正因数（除了 x 本身）被称为 x 的 真因数。

如果一个数字恰好仅有两个 真因数，则称该数字为 特殊数字。例如：

数字 4 是 特殊数字，因为它的真因数为 1 和 2。
数字 6 不是 特殊数字，因为它的真因数为 1、2 和 3。

返回区间 [l, r] 内 不是 特殊数字 的数字数量。



示例 1：

输入： l = 5, r = 7

输出： 3

解释：

区间 [5, 7] 内不存在特殊数字。



示例 2：

输入： l = 4, r = 16

输出： 11

解释：

区间 [4, 16] 内的特殊数字为 4 和 9。

 

提示：

1 <= l <= r <= 109
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int nonSpecialCount(int l, int r) {
        // 因子一般是成双成对的，若一个数字有奇数个因子，那么该数一定是平方数。
        // 该数除去自身和 1 仅有一个因子，因此该因子一定是质数。
        int n = sqrt(r);
        vector<int> v(n + 1); //统计质数，0表示是质数，1表示不是质数
        int res = r - l + 1;
        for (int i = 2; i <= n; i++) {
            if (v[i] == 0) {
                if (i * i >= l && i * i <= r) {
                    res--;
                }
                for (int j = i * 2; j <= n; j += i) {
                    v[j] = 1;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.nonSpecialCount(5, 7) << endl;
    cout << s.nonSpecialCount(4, 16) << endl;
    return 0;
}