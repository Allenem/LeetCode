/*
3138. 同位字符串连接的最小长度

给你一个字符串 s ，它由某个字符串 t 和若干 t  的 同位字符串 连接而成。

请你返回字符串 t 的 最小 可能长度。

同位字符串 指的是重新排列一个单词得到的另外一个字符串，原来字符串中的每个字符在新字符串中都恰好只使用一次。

 

示例 1：

输入：s = "abba"

输出：2

解释：

一个可能的字符串 t 为 "ba" 。




示例 2：

输入：s = "cdef"

输出：4

解释：

一个可能的字符串 t 为 "cdef" ，注意 t 可能等于 s 。

 

提示：

1 <= s.length <= 105
s 只包含小写英文字母。

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minAnagramLength(string s) {
        int n = s.length();
        for (int k = 1; k <= n / 2; k++) {
            if (n % k) {
                continue;
            }
            array<int, 26> cnt0{};
            for (int j = 0; j < k; j++) {
                cnt0[s[j] - 'a']++;
            }
            bool ok = true;
            for (int i = k * 2; i <= n; i += k) {
                array<int, 26> cnt{};
                for (int j = i - k; j < i; j++) {
                    cnt[s[j] - 'a']++;
                }
                if (cnt != cnt0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return k;
            }
        }
        return n;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/minimum-length-of-anagram-concatenation/solutions/2766442/mei-ju-n-de-yin-zi-zhi-duo-128-ge-python-u36n/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution s;
    string str = "abba";
    cout << s.minAnagramLength(str) << endl;
    str = "cdef";
    cout << s.minAnagramLength(str) << endl;
    return 0;
}