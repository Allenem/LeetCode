/*
3216. 交换后字典序最小的字符串

给你一个仅由数字组成的字符串 s，在最多交换一次 相邻 且具有相同 奇偶性 的数字后，返回可以得到的 字典序最小的字符串 。

如果两个数字都是奇数或都是偶数，则它们具有相同的奇偶性。例如，5 和 9、2 和 4 奇偶性相同，而 6 和 9 奇偶性不同。

(字典序更小
在字符串 a 和字符串 b 出现第一个不同的位置，如果字符串 a 有一个字母比字符串 b 中的对应字母在字母表中更早出现，则字符串 a 在字典序上小于字符串 b 。
如果前 min(a.length, b.length) 个字符没有不同，则较短的字符串在字段序上较小。)



示例 1：

输入： s = "45320"

输出： "43520"

解释：

s[1] == '5' 和 s[2] == '3' 都具有相同的奇偶性，交换它们可以得到字典序最小的字符串。



示例 2：

输入： s = "001"

输出： "001"

解释：

无需进行交换，因为 s 已经是字典序最小的。

 

提示：

2 <= s.length <= 100
s 仅由数字组成。
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string getSmallestString(string s) {
        string res = s.c_str(), tmp = s.c_str();
        for(int i = 1; i < s.size(); i++){
            if((s[i]%2==s[i-1]%2) && (s[i]<s[i-1])){
                tmp[i] = s[i-1];
                tmp[i-1] = s[i];
            }
            if(tmp<res){
                res = tmp.c_str();
            }
            tmp = s.c_str(); // 因为最多交换一次，所以要重置
        }
        return res;
    }
};

int main(){
    Solution s1;
    string s = "45320";
    cout << s1.getSmallestString(s) << endl;
    cout << "----------------" << endl;

    s = "001";
    cout << s1.getSmallestString(s) << endl;
    cout << "----------------" << endl;

    return 0;
}