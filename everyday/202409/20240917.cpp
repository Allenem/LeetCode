/*
815. 公交路线

给你一个数组 routes ，表示一系列公交线路，其中每个 routes[i] 表示一条公交线路，第 i 辆公交车将会在上面循环行驶。

例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... 这样的车站路线行驶。

现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。 期间仅可乘坐公交车。

求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 -1 。


示例 1：

输入：routes = [[1,2,7],[3,6,7]], source = 1, target = 6
输出：2
解释：最优策略是先乘坐第一辆公交车到达车站 7 , 然后换乘第二辆公交车到车站 6 。 


示例 2：

输入：routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
输出：-1
 

提示：

1 <= routes.length <= 500.
1 <= routes[i].length <= 105
routes[i] 中的所有值 互不相同
sum(routes[i].length) <= 105
0 <= routes[i][j] < 106
0 <= source, target < 106
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source==target) return 0;
        int minstep=1, n=routes.size();
        vector<bool> routevisit(n, false);
        // bfs queue
        queue<int> q;
        q.push(source);
        // hashmap[station]={routeidx1,routeidx2,...}
        unordered_map<int, vector<int>> hashmap(n);
        for(int i=0;i<n;i++){
            for(int x:routes[i]){
                hashmap[x].push_back(i);
            }
        }
        //bfs
        while(!q.empty()){
            for(int qsz=q.size();qsz>0;qsz--){
                int x=q.front();
                q.pop();
                for(int i:hashmap[x]){
                    if(!routevisit[i]){
                        routevisit[i]=true;
                        for(int station:routes[i]){
                            if(station==target)return minstep;
                            q.push(station);
                        }
                    }
                }
            }
            minstep++;
        }
        return -1;
    }
};

int main(){
    Solution s;
    vector<vector<int>> routes={{1,2,7},{3,6,7}};
    int source=1, target=6;
    cout<<s.numBusesToDestination(routes, source, target)<<endl;

    vector<vector<int>> routes2={{7,12},{4,5,15},{6},{15,19},{9,12,13}};
    source=15, target=12;
    cout<<s.numBusesToDestination(routes2, source, target)<<endl;
    return 0;
}