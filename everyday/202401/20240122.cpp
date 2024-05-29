/*
670. 最大交换

给定一个非负整数，你至多可以交换一次数字中的任意两位。返回你能得到的最大值。

示例 1 :

输入: 2736
输出: 7236
解释: 交换数字2和数字7。

示例 2 :

输入: 9973
输出: 9973
解释: 不需要交换。

注意:

给定数字的范围是 [0, 10^8]
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        vector<int> vnum, mami;
        while (num) {
            vnum.push_back(num % 10);
            mami.push_back(num % 10);
            num /= 10;
        }
        sort(mami.begin(), mami.end());
        int n = mami.size();
        for (int i = n - 1;i > -1;--i) {
            if (vnum[i] != mami[i]) {
                int idx = find(vnum.begin(), vnum.end(), mami[i]) - vnum.begin();
                swap(vnum[i], vnum[idx]);
                break;
            }
        }
        int ans = 0;
        for (int i = 0;i < n;++i) {
            ans += vnum[i] * pow(10, i);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.maximumSwap(2736) << endl;
    cout << sol.maximumSwap(9973) << endl;
    return 0;
}