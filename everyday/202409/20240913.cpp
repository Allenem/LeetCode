/*
2398. 预算内的最多机器人数目

你有 n 个机器人，给你两个下标从 0 开始的整数数组 chargeTimes 和 runningCosts ，两者长度都为 n 。第 i 个机器人充电时间为 chargeTimes[i] 单位时间，花费 runningCosts[i] 单位时间运行。再给你一个整数 budget 。

运行 k 个机器人 总开销 是 max(chargeTimes) + k * sum(runningCosts) ，其中 max(chargeTimes) 是这 k 个机器人中最大充电时间，sum(runningCosts) 是这 k 个机器人的运行时间之和。

请你返回在 不超过 budget 的前提下，你 最多 可以 连续 运行的机器人数目为多少。



示例 1：

输入：chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
输出：3
解释：
可以在 budget 以内运行所有单个机器人或者连续运行 2 个机器人。
选择前 3 个机器人，可以得到答案最大值 3 。总开销是 max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24 ，小于 25 。
可以看出无法在 budget 以内连续运行超过 3 个机器人，所以我们返回 3 。


示例 2：

输入：chargeTimes = [11,12,19], runningCosts = [10,8,7], budget = 19
输出：0
解释：即使运行任何一个单个机器人，还是会超出 budget，所以我们返回 0 。



提示：

chargeTimes.length == runningCosts.length == n
1 <= n <= 5 * 104
1 <= chargeTimes[i], runningCosts[i] <= 105
1 <= budget <= 1015
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        // 单调栈
        // max(chargeTimes) + k * sum(runningCosts) <= budget
        // 入：chargeTimes[right] 进入窗口时，弹出队尾的 ≤ chargeTimes[right] 的元素。
        // 出：如果总开销超过 budget，则不断移出左端点，直到总开销不超过 budget。特别地，如果左端点恰好等于队首，则弹出队首。
        // 更新答案：用窗口长度 right−left+1 更新答案的最大值。
        // ⚠注意：为了方便判断队首是否要出队，单调队列中保存的是下标。
        int ans = 0, left = 0;
        long long sum = 0;
        deque<int> q; // 单调递减 双端队列
        for(int right = 0; right < chargeTimes.size(); right++){

            // 1. 入
            while(!q.empty() && chargeTimes[right] >= chargeTimes[q.back()]){
                q.pop_back();
            }
            q.push_back(right);
            sum += runningCosts[right];

            // 2. 出
            while(!q.empty() && chargeTimes[q.front()] + (right - left + 1) * sum > budget){
                if(q.front() == left){
                    q.pop_front();
                }
                sum -= runningCosts[left++];
            }

            // 3. 更新答案
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> chargeTimes = {3,6,1,3,4};
    vector<int> runningCosts = {2,1,3,4,5};
    long long budget = 25;
    cout << s.maximumRobots(chargeTimes, runningCosts, budget) << endl;

    chargeTimes = {11,12,19};
    runningCosts = {10,8,7};
    budget = 19;
    cout << s.maximumRobots(chargeTimes, runningCosts, budget) << endl;
    
    return 0;
}