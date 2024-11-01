/*
3259. 超级饮料的最大强化能量

来自未来的体育科学家给你两个整数数组 energyDrinkA 和 energyDrinkB，数组长度都等于 n。这两个数组分别代表 A、B 两种不同能量饮料每小时所能提供的强化能量。

你需要每小时饮用一种能量饮料来 最大化 你的总强化能量。然而，如果从一种能量饮料切换到另一种，你需要等待一小时来梳理身体的能量体系（在那个小时里你将不会获得任何强化能量）。

返回在接下来的 n 小时内你能获得的 最大 总强化能量。

注意 你可以选择从饮用任意一种能量饮料开始。

 

示例 1：

输入：energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]

输出：5

解释：

要想获得 5 点强化能量，需要选择只饮用能量饮料 A（或者只饮用 B）。



示例 2：

输入：energyDrinkA = [4,1,1], energyDrinkB = [1,1,3]

输出：7

解释：

第一个小时饮用能量饮料 A。
切换到能量饮料 B ，在第二个小时无法获得强化能量。
第三个小时饮用能量饮料 B ，并获得强化能量。
 

提示：

n == energyDrinkA.length == energyDrinkB.length
3 <= n <= 105
1 <= energyDrinkA[i], energyDrinkB[i] <= 105
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        long long da0 = energyDrinkA[0], da1 = energyDrinkA[0] + energyDrinkA[1], da2 = 0;
        long long db0 = energyDrinkB[0], db1 = energyDrinkB[0] + energyDrinkB[1], db2 = 0;
        for(int i = 2; i < n; i++){
            da2 = max(da1, db0) + energyDrinkA[i];
            db2 = max(da0, db1) + energyDrinkB[i];
            da0 = da1, db0 = db1;
            da1 = da2, db1 = db2;
        }
        return max(da2, db2);
    }
};

int main(){
    Solution s;
    vector<int> energyDrinkA = {1,3,1};
    vector<int> energyDrinkB = {3,1,1};
    cout << s.maxEnergyBoost(energyDrinkA, energyDrinkB) << endl;

    energyDrinkA = {4,1,1};
    energyDrinkB = {1,1,3};
    cout << s.maxEnergyBoost(energyDrinkA, energyDrinkB) << endl;
    
    return 0;
}