/*
LCP 61. 气温变化趋势

力扣城计划在两地设立「力扣嘉年华」的分会场，气象小组正在分析两地区的气温变化趋势，对于第 i ~ (i+1) 天的气温变化趋势，将根据以下规则判断：

若第 i+1 天的气温 高于 第 i 天，为 上升 趋势
若第 i+1 天的气温 等于 第 i 天，为 平稳 趋势
若第 i+1 天的气温 低于 第 i 天，为 下降 趋势
已知 temperatureA[i] 和 temperatureB[i] 分别表示第 i 天两地区的气温。 组委会希望找到一段天数尽可能多，且两地气温变化趋势相同的时间举办嘉年华活动。请分析并返回两地气温变化趋势相同的最大连续天数。

即最大的 n，使得第 i~i+n 天之间，两地气温变化趋势相同

示例 1：

输入： temperatureA = [21,18,18,18,31] temperatureB = [34,32,16,16,17]

输出：2

解释：如下表所示， 第 2～4 天两地气温变化趋势相同，且持续时间最长，因此返回 4-2=2image.png

| 天数      | 0~1  | 1~2  | 2~3  | 3~4  |
| --------- | ---- | ---- | ---- | ---- |
| 变化趋势A | 下降 | 平稳 | 平稳 | 上升 |
| 变化趋势B | 下降 | 下降 | 平稳 | 上升 |


示例 2：

输入： temperatureA = [5,10,16,-6,15,11,3] temperatureB = [16,22,23,23,25,3,-16]

输出：3

提示：

2 <= temperatureA.length == temperatureB.length <= 1000
-20 <= temperatureA[i], temperatureB[i] <= 40
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int temperatureTrend(vector<int>& temperatureA, vector<int>& temperatureB) {
        int n = temperatureA.size(), ans = 0, tmp = 0;
        for (int i = 1;i < n;i++) {
            int a = temperatureA[i] - temperatureA[i - 1], b = temperatureB[i] - temperatureB[i - 1];
            if (a * b > 0 || a == b) {
                tmp++;
            }
            else {
                tmp = 0;
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> temperatureA = { 21,18,18,18,31 }, temperatureB = { 34,32,16,16,17 };
    cout << s.temperatureTrend(temperatureA, temperatureB) << endl;

    temperatureA = { 5,10,16,-6,15,11,3 }, temperatureB = { 16,22,23,23,25,3,-16 };
    cout << s.temperatureTrend(temperatureA, temperatureB) << endl;

    return 0;
}