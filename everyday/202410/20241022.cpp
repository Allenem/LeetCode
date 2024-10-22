/*
3184. 构成整天的下标对数目 I

给你一个整数数组 hours，表示以 小时 为单位的时间，返回一个整数，表示满足 i < j 且 hours[i] + hours[j] 构成 整天 的下标对 i, j 的数目。

整天 定义为时间持续时间是 24 小时的 整数倍 。

例如，1 天是 24 小时，2 天是 48 小时，3 天是 72 小时，以此类推。

 

示例 1：

输入： hours = [12,12,30,24,24]

输出： 2

解释：

构成整天的下标对分别是 (0, 1) 和 (3, 4)。



示例 2：

输入： hours = [72,48,24,3]

输出： 3

解释：

构成整天的下标对分别是 (0, 1)、(0, 2) 和 (1, 2)。

 

提示：

1 <= hours.length <= 100
1 <= hours[i] <= 109

*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int countCompleteDayPairs(vector<int>& hours) {
        // 注意12,24，其他的算了两遍
        // cntmod[i]*cntmod[24-i]/2 + cntmod[12]*(cntmod[12]-1)/2 + cntmod[0]*(cntmod[0]-1)/2
        int ans = 0, mod12 = 0, mod24 = 0;
        map<int, int> selfmod;
        for (int i = 0; i < 24; ++i) selfmod[i] = 0;
        
        for(int h: hours){
            selfmod[h%24]++;
            if(h%24==0) mod24++;
            else if(h%12==0) mod12++;
        }
        for(int i=0;i<24;i++) if(i!=0 && i!=12) ans += selfmod[i] * selfmod[24-i];
        return (ans + mod12*(mod12-1) + mod24*(mod24-1)) / 2;
    }
};

int main(){
    Solution s;
    vector<int> hours = {12,12,30,24,24};
    cout << s.countCompleteDayPairs(hours) << endl;

    vector<int> hours2 = {72,48,24,3};
    cout << s.countCompleteDayPairs(hours2) << endl;
    
    return 0;
}