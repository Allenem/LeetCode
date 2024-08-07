/*
2707. 字符串中的额外字符

给你一个下标从 0 开始的字符串 s 和一个单词字典 dictionary 。你需要将 s 分割成若干个 互不重叠 的子字符串，每个子字符串都在 dictionary 中出现过。s 中可能会有一些 额外的字符 不在任何子字符串中。

请你采取最优策略分割 s ，使剩下的字符 最少 。

示例 1：

输入：s = "leetscode", dictionary = ["leet","code","leetcode"]
输出：1
解释：将 s 分成两个子字符串：下标从 0 到 3 的 "leet" 和下标从 5 到 8 的 "code" 。只有 1 个字符没有使用（下标为 4），所以我们返回 1 。

示例 2：

输入：s = "sayhelloworld", dictionary = ["hello","world"]
输出：3
解释：将 s 分成两个子字符串：下标从 3 到 7 的 "hello" 和下标从 8 到 12 的 "world" 。下标为 0 ，1 和 2 的字符没有使用，所以我们返回 3 。

提示：

1 <= s.length <= 50
1 <= dictionary.length <= 50
1 <= dictionary[i].length <= 50
dictionary[i] 和 s 只包含小写英文字母。
dictionary 中的单词互不相同。
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        set<string> vis;
        for (auto& di : dictionary)
            vis.insert(di);
        int n = s.size();
        int p[n];
        for (int i = 0; i < n; i++) {
            p[i] = vis.count(s.substr(0, i + 1)) ? 0 : i + 1;
            for (int j = 0; j < i; j++) {
                if (vis.count(s.substr(j + 1, i - j)))
                    p[i] = min(p[i], p[j]);
                else
                    p[i] = min(p[i], p[j] + i - j);
            }
        }
        return p[n - 1];
    }
};

int main() {
    Solution s;
    string str = "leetscode";
    vector<string> dictionary = { "leet", "code", "leetcode" };
    cout << s.minExtraChar(str, dictionary) << endl;

    str = "sayhelloworld";
    dictionary = { "hello", "world" };
    cout << s.minExtraChar(str, dictionary) << endl;

    return 0;
}