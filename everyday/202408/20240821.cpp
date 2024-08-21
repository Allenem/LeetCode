/*
3007. 价值和小于等于 K 的最大数字

给你一个整数 k 和一个整数 x 。整数 num 的价值是它的二进制表示中在 x，2x，3x 等位置处 设置位  的数目（从最低有效位开始）。下面的表格包含了如何计算价值的例子。

x	num	Binary Representation	Price
1	13	000001101	3
2	13	000001101	1
2	233	011101001	3
3	13	000001101	1
3	362	101101010	2

num 的 累加价值 是从 1 到 num 的数字的 总 价值。如果 num 的累加价值小于或等于 k 则被认为是 廉价 的。

请你返回 最大 的廉价数字。


示例 1：

输入：k = 9, x = 1
输出：6
解释：由下表所示，6 是最大的廉价数字。
x	num	Binary Representation	Price	Accumulated Price
1	1	001	1	1
1	2	010	1	2
1	3	011	2	4
1	4	100	1	5
1	5	101	2	7
1	6	110	2	9
1	7	111	3	12


示例 2：

输入：k = 7, x = 2
输出：9
解释：由下表所示，9 是最大的廉价数字。
x	num	Binary Representation	Price	Accumulated Price
2	1	0001	0	0
2	2	0010	1	1
2	3	0011	1	2
2	4	0100	0	2
2	5	0101	0	2
2	6	0110	1	3
2	7	0111	1	4
2	8	1000	1	5
2	9	1001	1	6
2	10	1010	2	8


提示：

1 <= k <= 1015
1 <= x <= 8
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    long long findMaximumNumber(long long k, int x)
    {
        long long l = 1, r = (k + 1) << x;
        while (l <= r)
        {
            long long m = l + ((r - l) >> 1), mm = m + 1, a = 0;
            int c = 64 - (m ? __builtin_clzll(m) : 0);
            // 模拟统计每一位有效位的1的数
            // 单一位从01到0011循环长度不断乘2
            // 0000
            // 0001
            // 0010
            // 0011
            // 0100
            // 0101
            // 0110
            // 0111
            // 1000
            for (int i = x; i <= c; i += x)
            {
                a += (mm / (1LL << i) << (i - 1)) + max(0LL, mm % (1LL << i) - (1LL << (i - 1)));
            }
            if (a <= k)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return r;
    }
};

int main()
{
    Solution s;
    cout << s.findMaximumNumber(9, 1) << endl;
    cout << s.findMaximumNumber(7, 2) << endl;
    return 1;
}