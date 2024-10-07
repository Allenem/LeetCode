/*
871. 最低加油次数

汽车从起点出发驶向目的地，该目的地位于出发位置东面 target 英里处。

沿途有加油站，用数组 stations 表示。其中 stations[i] = [positioni, fueli] 表示第 i 个加油站位于出发位置东面 positioni 英里处，并且有 fueli 升汽油。

假设汽车油箱的容量是无限的，其中最初有 startFuel 升燃料。它每行驶 1 英里就会用掉 1 升汽油。当汽车到达加油站时，它可能停下来加油，将所有汽油从加油站转移到汽车中。

为了到达目的地，汽车所必要的最低加油次数是多少？如果无法到达目的地，则返回 -1 。

注意：如果汽车到达加油站时剩余燃料为 0，它仍然可以在那里加油。如果汽车到达目的地时剩余燃料为 0，仍然认为它已经到达目的地。


示例 1：

输入：target = 1, startFuel = 1, stations = []
输出：0
解释：可以在不加油的情况下到达目的地。


示例 2：

输入：target = 100, startFuel = 1, stations = [[10,100]]
输出：-1
解释：无法抵达目的地，甚至无法到达第一个加油站。


示例 3：

输入：target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
输出：2
解释：
出发时有 10 升燃料。
开车来到距起点 10 英里处的加油站，消耗 10 升燃料。将汽油从 0 升加到 60 升。
然后，从 10 英里处的加油站开到 60 英里处的加油站（消耗 50 升燃料），
并将汽油从 10 升加到 50 升。然后开车抵达目的地。
沿途在两个加油站停靠，所以返回 2 。


提示：

1 <= target, startFuel <= 109
0 <= stations.length <= 500
1 <= positioni < positioni+1 < target
1 <= fueli < 109
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n=stations.size(), prestop=0, curstop=0, cnt=0, fuel=startFuel;
        // 贪心，先加油油多的站点，用优先队列（大顶堆）
        priority_queue <int,vector<int>,less<int>> prestopfuel;
        // +1是target
        for(int i=0;i<n+1;i++){
            curstop=i<n?stations[i][0]:target;
            fuel-=curstop-prestop;
            // 油不够了，而且前面有油站，加油
            while(fuel<0&&!prestopfuel.empty()){
                fuel+=prestopfuel.top();
                prestopfuel.pop();
                cnt++;
            }
            // 前面所有油站加油后还不够，返回-1
            if(fuel<0)return -1;
            // 油站信息入队
            if(i<n){
                prestopfuel.push(stations[i][1]);
                prestop=curstop;
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    int target=1, startFuel=1;
    vector<vector<int>> stations={};
    cout<<s.minRefuelStops(target,startFuel,stations)<<endl;

    target=100, startFuel=1;
    stations={{10,100}};
    cout<<s.minRefuelStops(target,startFuel,stations)<<endl;

    target=100, startFuel=10;
    stations={{10,60},{20,30},{30,30},{60,40}};
    cout<<s.minRefuelStops(target,startFuel,stations)<<endl;

    return 0;
}