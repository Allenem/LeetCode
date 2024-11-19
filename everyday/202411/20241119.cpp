/*
3243. 新增道路查询后的最短距离 I

给你一个整数 n 和一个二维整数数组 queries。

有 n 个城市，编号从 0 到 n - 1。初始时，每个城市 i 都有一条单向道路通往城市 i + 1（ 0 <= i < n - 1）。

queries[i] = [ui, vi] 表示新建一条从城市 ui 到城市 vi 的单向道路。每次查询后，你需要找到从城市 0 到城市 n - 1 的最短路径的长度。

返回一个数组 answer，对于范围 [0, queries.length - 1] 中的每个 i，answer[i] 是处理完前 i + 1 个查询后，从城市 0 到城市 n - 1 的最短路径的长度。

 

示例 1：

输入： n = 5, queries = [[2, 4], [0, 2], [0, 4]]

输出： [3, 2, 1]

解释：

新增一条从 2 到 4 的道路后，从 0 到 4 的最短路径长度为 3。

新增一条从 0 到 2 的道路后，从 0 到 4 的最短路径长度为 2。

新增一条从 0 到 4 的道路后，从 0 到 4 的最短路径长度为 1。



示例 2：

输入： n = 4, queries = [[0, 3], [0, 2]]

输出： [1, 1]

解释：

新增一条从 0 到 3 的道路后，从 0 到 3 的最短路径长度为 1。

新增一条从 0 到 2 的道路后，从 0 到 3 的最短路径长度仍为 1。

 

提示：

3 <= n <= 500
1 <= queries.length <= 500
queries[i].length == 2
0 <= queries[i][0] < queries[i][1] < n
1 < queries[i][1] - queries[i][0]
查询中没有重复的道路。
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        int ql = queries.size();
        vector<vector<int>> end(n); // 以n为end的所有前一个
        vector<int> f(n), ans(ql);
        iota(f.begin(), f.end(), 0);

        for(int qi=0; qi<ql; qi++){
            int l = queries[qi][0], r = queries[qi][1];
            end[r].push_back(l);
            if(f[l] + 1 < f[r]){
                f[r] = f[l] + 1;
                // 更新r后面，和以r结尾的
                for(int j = r+1; j<n; j++){
                    f[j] = min(f[j], f[j-1] + 1);
                    for(int i:end[j]) f[j] = min(f[j], f[i] + 1);
                }
            }
            ans[qi] = f[n-1];
        }

        return ans;
    }
};

int main(){
    Solution s;
    vector<vector<int>> queries = {{2, 4}, {0, 2}, {0, 4}};
    vector<int> ans = s.shortestDistanceAfterQueries(5, queries);
    for(int i:ans) cout << i << " ";
    cout << endl;

    queries = {{0, 3}, {0, 2}};
    ans = s.shortestDistanceAfterQueries(4, queries);
    for(int i:ans) cout << i << " ";
    cout << endl;
    return 0;
}