/*
3181. 执行操作可获得的最大总奖励 II

给你一个整数数组 rewardValues，长度为 n，代表奖励的值。

最初，你的总奖励 x 为 0，所有下标都是 未标记 的。你可以执行以下操作 任意次 ：

从区间 [0, n - 1] 中选择一个 未标记 的下标 i。
如果 rewardValues[i] 大于 你当前的总奖励 x，则将 rewardValues[i] 加到 x 上（即 x = x + rewardValues[i]），并 标记 下标 i。
以整数形式返回执行最优操作能够获得的 最大 总奖励。

 

示例 1：

输入：rewardValues = [1,1,3,3]

输出：4

解释：

依次标记下标 0 和 2，总奖励为 4，这是可获得的最大值。



示例 2：

输入：rewardValues = [1,6,4,3,2]

输出：11

解释：

依次标记下标 0、2 和 1。总奖励为 11，这是可获得的最大值。

 

提示：

1 <= rewardValues.length <= 5 * 104
1 <= rewardValues[i] <= 5 * 104
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <bitset>
using namespace std;

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        int m = ranges::max(rewardValues);
        unordered_set<int> s;
        for(int v:rewardValues){
            if(s.contains(v)) continue;
            // 如果数组中包含 m−1，则答案为 2m−1
            // 如果有两个不同元素之和等于 m−1，也可以直接返回 2m−1
            if(v == m-1 || s.contains(m-1-v)) return 2*m-1;
            s.insert(v);
        }

        // 排序，去重
        ranges::sort(rewardValues);
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        bitset<100'000> dp{1};
        for(int v:rewardValues){
            int shift = dp.size() - v;
            // 左移 shift 再右移 shift，把所有 >= v 的比特位置 0
            // dp |= dp << shift >> shift << v;
            dp |= dp << shift >> (shift - v); // 简化上式
        }
        // 答案为 dp 的最高位，即 dp 的二进制长度减一
        for(int i = 2*rewardValues.back()-1;;i--){
            if(dp.test(i)) return i;
        }
    }
};

int main(){
    Solution s;
    vector<int> rewardValues = {1,1,3,3};
    cout << s.maxTotalReward(rewardValues) << endl;
    rewardValues = {1,6,4,3,2};
    cout << s.maxTotalReward(rewardValues) << endl;
    return 0;
}
// g++ 20241026.cpp -std=c++20