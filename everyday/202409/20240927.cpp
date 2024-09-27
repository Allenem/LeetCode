/*
2516. 每种字符至少取 K 个

给你一个由字符 'a'、'b'、'c' 组成的字符串 s 和一个非负整数 k 。每分钟，你可以选择取走 s 最左侧 还是 最右侧 的那个字符。

你必须取走每种字符 至少 k 个，返回需要的 最少 分钟数；如果无法取到，则返回 -1 。


示例 1：

输入：s = "aabaaaacaabc", k = 2
输出：8
解释：
从 s 的左侧取三个字符，现在共取到两个字符 'a' 、一个字符 'b' 。
从 s 的右侧取五个字符，现在共取到四个字符 'a' 、两个字符 'b' 和两个字符 'c' 。
共需要 3 + 5 = 8 分钟。
可以证明需要的最少分钟数是 8 。


示例 2：

输入：s = "a", k = 1
输出：-1
解释：无法取到一个字符 'b' 或者 'c'，所以返回 -1 。
 

提示：

1 <= s.length <= 105
s 仅由字母 'a'、'b'、'c' 组成
0 <= k <= s.length
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class Solution {
public:
    int takeCharacters(string s, int k) {
        // 理解成截取一个子字符串，把这个子字符串刨掉后剩下的每种字符都>=k个。
        vector<int>cnt(3),subcnt(3);
        for(auto c:s) cnt[c-'a']++;
        if(cnt[0]<k||cnt[1]<k||cnt[2]<k)return -1;
        int n=s.size(),mx=0,l=0,r=0;
        while(r<n){
            subcnt[s[r]-'a']++;
            while(cnt[0]-subcnt[0]<k || cnt[1]-subcnt[1]<k || cnt[2]-subcnt[2]<k){
                subcnt[s[l++]-'a']--;
            }
            mx=max(mx,r-l+1);
            r++;
        }
        return n-mx;
    }
};

int main() {
    Solution s;
    cout << s.takeCharacters("aabaaaacaabc", 2) << endl;
    cout << s.takeCharacters("a", 1) << endl;
    return 0;
}