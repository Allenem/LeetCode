/*
2710. 移除字符串中的尾随零

给你一个用字符串表示的正整数 num ，请你以字符串形式返回不含尾随零的整数 num 。

示例 1：

输入：num = "51230100"
输出："512301"
解释：整数 "51230100" 有 2 个尾随零，移除并返回整数 "512301" 。

示例 2：

输入：num = "123"
输出："123"
解释：整数 "123" 不含尾随零，返回整数 "123" 。

提示：

1 <= num.length <= 1000
num 仅由数字 0 到 9 组成
num 不含前导零
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string removeTrailingZeros(string num) {
        for (int i = num.size() - 1;i > -1;i--) {
            if (num[i] != '0') return num.substr(0, i + 1);
        }
        return "";
    }
};

int main() {
    Solution s;
    cout << s.removeTrailingZeros("51230100") << endl;
    cout << s.removeTrailingZeros("123") << endl;
    return 0;
}