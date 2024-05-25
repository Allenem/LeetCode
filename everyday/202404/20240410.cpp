/*
1702. 修改后的最大二进制字符串

给你一个二进制字符串 binary ，它仅有 0 或者 1
组成。你可以使用下面的操作任意次对它进行修改：

操作 1 ：如果二进制串包含子字符串 "00" ，你可以用 "10" 将其替换。
比方说， "00010" -> "10010"

操作 2 ：如果二进制串包含子字符串 "10" ，你可以用 "01" 将其替换。
比方说， "00010" -> "00001"

请你返回执行上述操作任意次以后能得到的 最大二进制字符串 。如果二进制字符串 x
对应的十进制数字大于二进制字符串 y 对应的十进制数字，那么我们称二进制字符串 x
大于二进制字符串 y 。

示例 1：

输入：binary = "000110"
输出："111011"
解释：一个可行的转换为：
"000110" -> "000101"
"000101" -> "100101"
"100101" -> "110101"
"110101" -> "110011"
"110011" -> "111011"

示例 2：

输入：binary = "01"
输出："01"
解释："01" 没办法进行任何转换。

提示：

1 <= binary.length <= 10^5
binary 仅包含 '0' 和 '1' 。
*/

#include <limits.h>
#include <iostream>
#include <string>
using namespace std;

class Solution {
   public:
    string maximumBinaryString(string binary) {
        int n = binary.size(), zerocnt = 0, begin = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (binary[i] == '0') {
                zerocnt++;
                begin = min(begin, i);
            }
        }
        if (zerocnt < 2)
            return binary;
        string ret(n, '1');
        ret[begin + zerocnt - 1] = '0';
        return ret;
    }
};

int main() {
    Solution s;
    cout << s.maximumBinaryString("000110") << endl;
    cout << s.maximumBinaryString("01") << endl;
    return 0;
}