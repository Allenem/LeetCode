/*
3211. 生成不含相邻零的二进制字符串

给你一个正整数 n。

如果一个二进制字符串 x 的所有长度为 2 的 子字符串 （子字符串 是字符串中连续的 非空 字符序列。）中包含 至少 一个 "1"，则称 x 是一个 有效 字符串。

返回所有长度为 n 的 有效 字符串，可以以任意顺序排列。



示例 1：

输入： n = 3

输出： ["010","011","101","110","111"]

解释：

长度为 3 的有效字符串有："010"、"011"、"101"、"110" 和 "111"。



示例 2：

输入： n = 1

输出： ["0","1"]

解释：

长度为 1 的有效字符串有："0" 和 "1"。

 

提示：

1 <= n <= 18
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> validStrings(int n) {
        vector<string> ans;
        string str;

        function<void(string &)> dfs = [&](string& s) {
            if(s.size() == n){
                ans.push_back(s);
                return;
            }
            if(s.empty() || s.back() == '1'){
                s.push_back('0');
                dfs(s);
                s.pop_back();
            }
            s.push_back('1');
            dfs(s);
            s.pop_back();
        };

        dfs(str);
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> ans = s.validStrings(3);
    for(auto str : ans){
        cout << str << endl;
    }
    cout << endl;
    ans = s.validStrings(1);
    for(auto str : ans){
        cout << str << endl;
    }
    return 0;
}