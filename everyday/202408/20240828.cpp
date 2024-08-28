/*
3144. 分割字符频率相等的最少子字符串

给你一个字符串 s ，你需要将它分割成一个或者更多的 平衡 子字符串。比方说，s == "ababcc" 那么 ("abab", "c", "c") ，("ab", "abc", "c") 和 ("ababcc") 都是合法分割，但是 ("a", "bab", "cc") ，("aba", "bc", "c") 和 ("ab", "abcc") 不是，不平衡的子字符串用粗体表示。

请你返回 s 最少 能分割成多少个平衡子字符串。

注意：一个 平衡 字符串指的是字符串中所有字符出现的次数都相同。

 

示例 1：

输入：s = "fabccddg"

输出：3

解释：

我们可以将 s 分割成 3 个子字符串：("fab, "ccdd", "g") 或者 ("fabc", "cd", "dg") 。



示例 2：

输入：s = "abababaccddb"

输出：2

解释：

我们可以将 s 分割成 2 个子字符串：("abab", "abaccddb") 。

 

提示：

1 <= s.length <= 1000
s 只包含小写英文字母。
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    static const int inf;
    int minimumSubstringsInPartition(string s) {
        int n = s.size();
        vector<int> d(n + 1, inf);
        unordered_map<char, int> occ_cnt;
        d[0] = 0;
        for (int i = 1; i <= n; i++) {
            int max_cnt = 0;
            occ_cnt.clear();
            for (int j = i; j >= 1; j--) {
                occ_cnt[s[j - 1]]++;
                max_cnt = max(max_cnt, occ_cnt[s[j - 1]]);
                if (max_cnt * occ_cnt.size() == (i - j + 1) && d[j - 1] != inf) {
                    d[i] = min(d[i], d[j - 1] + 1);
                }
            }
        }
        return d[n];
    }
};
const int Solution::inf = 0x3f3f3f3f;

int main() {
    Solution solution;
    string s = "fabccddg";
    cout << solution.minimumSubstringsInPartition(s) << endl;
    s = "abababaccddb";
    cout << solution.minimumSubstringsInPartition(s) << endl;
    return 0;
}