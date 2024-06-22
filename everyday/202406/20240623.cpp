/*
520. 检测大写字母

我们定义，在以下情况时，单词的大写用法是正确的：

全部字母都是大写，比如 "USA" 。
单词中所有字母都不是大写，比如 "leetcode" 。
如果单词不只含有一个字母，只有首字母大写， 比如 "Google" 。

给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false 。

示例 1：

输入：word = "USA"
输出：true

示例 2：

输入：word = "FlaG"
输出：false

提示：

1 <= word.length <= 100
word 由小写和大写英文字母组成
*/
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool detectCapitalUse(string word) {
        // A~Z 65~90, a~z 97~122
        if (all_of(word.begin(), word.end(), [](char ch) { return ch <= 'Z'; })) return true;
        if (all_of(word.begin(), word.end(), [](char ch) { return ch >= 'a'; })) return true;
        if (word[0] <= 'Z' && all_of(word.begin() + 1, word.end(), [](char ch) { return ch >= 'a'; })) return true;
        return false;
    }
};

int main() {
    Solution sol;
    cout << sol.detectCapitalUse("USA") << endl;
    cout << sol.detectCapitalUse("FlaG") << endl;
    return 0;
}