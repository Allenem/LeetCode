/*
633. 平方数之和

给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c 。



示例 1：

输入：c = 5
输出：true
解释：1 * 1 + 2 * 2 = 5


示例 2：

输入：c = 3
输出：false
 

提示：

0 <= c <= 231 - 1
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        for (int a = 0; a * a <= c / 2; a++) {
            int b = sqrt(c - a * a);
            if (a * a + b * b == c) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution solution;
    cout << boolalpha;
    cout << solution.judgeSquareSum(5) << endl;
    cout << solution.judgeSquareSum(3) << endl;
    return 0;
}