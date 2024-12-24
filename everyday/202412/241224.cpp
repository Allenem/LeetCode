/*
1705. 吃苹果的最大数目

有一棵特殊的苹果树，一连 n 天，每天都可以长出若干个苹果。在第 i 天，树上会长出 apples[i] 个苹果，这些苹果将会在 days[i] 天后（也就是说，第 i + days[i] 天时）腐烂，变得无法食用。也可能有那么几天，树上不会长出新的苹果，此时用 apples[i] == 0 且 days[i] == 0 表示。

你打算每天 最多 吃一个苹果来保证营养均衡。注意，你可以在这 n 天之后继续吃苹果。

给你两个长度为 n 的整数数组 days 和 apples ，返回你可以吃掉的苹果的最大数目。

 

示例 1：

输入：apples = [1,2,3,5,2], days = [3,2,1,4,2]
输出：7
解释：你可以吃掉 7 个苹果：
- 第一天，你吃掉第一天长出来的苹果。
- 第二天，你吃掉一个第二天长出来的苹果。
- 第三天，你吃掉一个第二天长出来的苹果。过了这一天，第三天长出来的苹果就已经腐烂了。
- 第四天到第七天，你吃的都是第四天长出来的苹果。



示例 2：

输入：apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
输出：5
解释：你可以吃掉 5 个苹果：
- 第一天到第三天，你吃的都是第一天长出来的苹果。
- 第四天和第五天不吃苹果。
- 第六天和第七天，你吃的都是第六天长出来的苹果。
 

提示：

apples.length == n
days.length == n
1 <= n <= 2 * 104
0 <= apples[i], days[i] <= 2 * 104
只有在 apples[i] = 0 时，days[i] = 0 才成立
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using pii = pair<int, int>;
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int ans = 0, n = apples.size(), i = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        // 1. 第一阶段是第 0 天到第 n−1 天
        while(i < n) {
            // 1.1 无法食用的去除
            while(!pq.empty() && pq.top().first <= i) pq.pop();
            
            // 1.2 根据 days 和 apples 的当前元素计算当天长出的苹果的腐烂日期和数量，如果数量大于 0，则将腐烂日期和数量加入优先队列
            int rottenDay = i + days[i], cnt = apples[i];
            if(cnt > 0) pq.emplace(rottenDay, cnt);

            // 1.3 如果优先队列不为空，则当天可以吃 1 个苹果，将优先队列的队首元素的数量减 1;
            // 如果队首元素的数量变成 0 则将队首元素取出。
            if(!pq.empty()) {
                pii curr = pq.top();
                pq.pop();
                curr.second--;
                if(curr.second != 0) pq.emplace(curr.first, curr.second);
                ans++;
            }
            i++;
        }

        // 2. 由于树上不会再长出苹果，因此只需要考虑能吃到的苹果数量。由于优先队列中的每个元素的数量可能很大，因此需要根据当前日期和优先队列的队首元素的腐烂日期和数量计算能吃到的苹果数量
        while(!pq.empty()){
            // 2.1 无法食用的去除
            while(!pq.empty() && pq.top().first <= i) pq.pop();

            if(pq.empty()) break;

            // 2.2 取出num = min 腐烂日距离当前i的天数，队首数量，
            pii curr = pq.top();
            pq.pop();
            int num = min(curr.first - i, curr.second);
            ans += num;
            i += num;
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<int> apples = {1,2,3,5,2};
    vector<int> days = {3,2,1,4,2};
    cout << s.eatenApples(apples, days) << endl;

    apples = {3,0,0,0,0,2};
    days = {3,0,0,0,0,2};
    cout << s.eatenApples(apples, days) << endl;
    
    return 0;
}