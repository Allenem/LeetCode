/*
383. 赎金信

给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

如果可以，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。

示例 1：

输入：ransomNote = "a", magazine = "b"
输出：false

示例 2：

输入：ransomNote = "aa", magazine = "ab"
输出：false

示例 3：

输入：ransomNote = "aa", magazine = "aab"
输出：true

提示：

1 <= ransomNote.length, magazine.length <= 105
ransomNote 和 magazine 由小写英文字母组成
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size() > magazine.size())
            return false;
        vector<int> cnt(26);
        for (char& s : magazine) {
            cnt[s - 'a']++;
        }
        for (char& s : ransomNote) {
            cnt[s - 'a']--;
            if (cnt[s - 'a'] < 0)
                return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    string ransomNote = "a", magazine = "b";
    cout << s.canConstruct(ransomNote, magazine) << endl;

    ransomNote = "aa", magazine = "ab";
    cout << s.canConstruct(ransomNote, magazine) << endl;

    ransomNote = "aa", magazine = "aab";
    cout << s.canConstruct(ransomNote, magazine) << endl;
    return 0;
}