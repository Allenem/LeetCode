/*
466. 统计重复个数

定义 str = [s, n] 表示 str 由 n 个字符串 s 连接构成。

例如，str == ["abc", 3] =="abcabcabc" 。
如果可以从 s2 中删除某些字符使其变为 s1，则称字符串 s1 可以从字符串 s2 获得。

例如，根据定义，s1 = "abc" 可以从 s2 = "abdbec" 获得，仅需要删除加粗且用斜体标识的字符。
现在给你两个字符串 s1 和 s2 和两个整数 n1 和 n2 。由此构造得到两个字符串，其中 str1 = [s1, n1]、str2 = [s2, n2] 。

请你找出一个最大整数 m ，以满足 str = [str2, m] 可以从 str1 获得。

示例 1：

输入：s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
输出：2

示例 2：

输入：s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
输出：1

提示：

1 <= s1.length, s2.length <= 100
s1 和 s2 由小写英文字母组成
1 <= n1, n2 <= 106
*/
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {

        //动态规划，求s2,从第一个开始到第n个开始，分别能走多少圈，结尾是哪个
        int result = 0;

        if (n1 == 0 || n2 == 0) {
            return result;
        }
        int s1Length = s1.size();
        int s2Length = s2.size();

        int dp[s2Length][2];//第i个字符开始和s1匹配，是s2能在单次s1的长度中出现的次数，以及下一次匹配s2开始的字符
        int begin, tmpResult;
        //计算dp的值
        for (int i = 0; i < s2Length; i++) {
            begin = i, tmpResult = 0;
            for (int j = 0; j < s1Length; j++) {
                if (s1[j] == s2[begin]) {
                    begin++;
                }
                if (begin == s2Length) {
                    begin = 0;
                    tmpResult++;
                }
            }
            dp[i][0] = tmpResult;
            dp[i][1] = begin;
        }

        result = 0;
        begin = 0;
        //计算s2出现的总次数
        for (int i = 0; i < n1; i++) {
            result += dp[begin][0];
            begin = dp[begin][1];
        }
        result = result / n2;

        return result;
    }
};

int main() {
    Solution sol;
    string s1 = "acb", s2 = "ab";
    int n1 = 4, n2 = 2;
    cout << sol.getMaxRepetitions(s1, n1, s2, n2) << endl;
    s1 = "acb", s2 = "acb";
    n1 = 1, n2 = 1;
    cout << sol.getMaxRepetitions(s1, n1, s2, n2) << endl;
    return 0;
}