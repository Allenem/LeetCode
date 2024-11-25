/*
743. 网络延迟时间

有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。



示例 1：

      2
    /   \
   v     v
   1     3
        /
       v
       4

输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
输出：2


示例 2：

输入：times = [[1,2,1]], n = 2, k = 1
输出：1


示例 3：

输入：times = [[1,2,1]], n = 2, k = 2
输出：-1
 

提示：

1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
所有 (ui, vi) 对都 互不相同（即，不含重复边）
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 邻接表
        vector<vector<pair<int, int>>> g(n); // source, target, distance
        for(auto& t:times) g[t[0]-1].emplace_back(t[1]-1, t[2]);

        vector<int> dist(n, INT_MAX); // n distance
        dist[k-1] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // distance, idx，小根堆
        pq.emplace(0, k-1);

        while(!pq.empty()){
            auto [dx, x] = pq.top();
            pq.pop();
            if(dx > dist[x]) continue; // x 之前出过堆，距离更小，所以不用更新
            for(auto& [y, d]:g[x]){
                int newd = dx + d;
                if(newd < dist[y]){
                    dist[y] = newd;       // 更新x邻居的最短路
                    pq.emplace(newd, y);  // 加入小根堆
                }
            }
        }

        int mx = ranges::max(dist);
        return mx < INT_MAX ? mx : -1;
    }
};

int main(){
    Solution s;
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4, k = 2;
    cout << s.networkDelayTime(times, n, k) << endl;

    times = {{1,2,1}};
    n = 2, k = 1;
    cout << s.networkDelayTime(times, n, k) << endl;

    times = {{1,2,1}};
    n = 2, k = 2;
    cout << s.networkDelayTime(times, n, k) << endl;
    return 0;
}
// g++ 20241125.cpp -std=c++20