/*
935. 骑士拨号器

象棋骑士有一个独特的移动方式，它可以垂直移动两个方格，水平移动一个方格，或者水平移动两个方格，垂直移动一个方格(两者都形成一个 L 的形状)。

象棋骑士可能的移动方式如下图所示:

https://assets.leetcode.com/uploads/2020/08/18/chess.jpg

我们有一个象棋骑士和一个电话垫，如下所示，骑士只能站在一个数字单元格上(即蓝色单元格)。

https://assets.leetcode.com/uploads/2020/08/18/phone.jpg

给定一个整数 n，返回我们可以拨多少个长度为 n 的不同电话号码。

你可以将骑士放置在任何数字单元格上，然后你应该执行 n - 1 次移动来获得长度为 n 的号码。所有的跳跃应该是有效的骑士跳跃。

因为答案可能很大，所以输出答案模 109 + 7.


示例 1：

输入：n = 1
输出：10
解释：我们需要拨一个长度为1的数字，所以把骑士放在10个单元格中的任何一个数字单元格上都能满足条件。


示例 2：

输入：n = 2
输出：20
解释：我们可以拨打的所有有效号码为[04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]


示例 3：

输入：n = 3131
输出：136006598
解释：注意取模
 

提示：

1 <= n <= 5000
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Solution {
public:
    int knightDialer(int n) {
        const int mod = 1e9 + 7;
        vector<vector<long long>> f(n, vector<long long>(10));
        for (int i = 0; i < 10; i++) {
            f[0][i] = 1;
        }
        for (int i = 1; i < n; i++) {
            f[i][0] = (f[i][0] + f[i - 1][4] + f[i - 1][6]) % mod;
            f[i][1] = (f[i][1] + f[i - 1][8] + f[i - 1][6]) % mod;
            f[i][2] = (f[i][2] + f[i - 1][7] + f[i - 1][9]) % mod;
            f[i][3] = (f[i][3] + f[i - 1][4] + f[i - 1][8]) % mod;
            f[i][4] = (f[i][4] + f[i - 1][3] + f[i - 1][9] + f[i - 1][0]) % mod;
            f[i][6] = (f[i][6] + f[i - 1][1] + f[i - 1][7] + f[i - 1][0]) % mod;
            f[i][7] = (f[i][7] + f[i - 1][2] + f[i - 1][6]) % mod;
            f[i][8] = (f[i][8] + f[i - 1][1] + f[i - 1][3]) % mod;
            f[i][9] = (f[i][9] + f[i - 1][2] + f[i - 1][4]) % mod;
        }
        long long sum = 0;
        for (int i = 0; i < 10; i++) {
            sum = (sum + f[n - 1][i]) % mod;
        }
        return sum;
    }
};

int main() {
    Solution sol;
    cout << sol.knightDialer(1) << endl;
    cout << sol.knightDialer(2) << endl;
    cout << sol.knightDialer(3131) << endl;
    return 0;
}