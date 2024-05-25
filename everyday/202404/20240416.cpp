/*
924. 尽量减少恶意软件的传播

给出了一个由 n 个节点组成的网络，用 n × n 个邻接矩阵图 graph
表示。在节点网络中，当 graph[i][j] = 1 时，表示节点 i 能够直接连接到另一个节点
j。

一些节点 initial
最初被恶意软件感染。只要两个节点直接连接，且其中至少一个节点受到恶意软件的感染，那么两个节点都将被恶意软件感染。这种恶意软件的传播将继续，直到没有更多的节点可以被这种方式感染。

假设 M(initial) 是在恶意软件停止传播之后，整个网络中感染恶意软件的最终节点数。

如果从 initial 中移除某一节点能够最小化 M(initial)，
返回该节点。如果有多个节点满足条件，就返回索引最小的节点。

请注意，如果某个节点已从受感染节点的列表 initial
中删除，它以后仍有可能因恶意软件传播而受到感染。

示例 1：

输入：graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
输出：0

示例 2：

输入：graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
输出：0

示例 3：

输入：graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
输出：1

提示：

n == graph.length
n == graph[i].length
2 <= n <= 300
graph[i][j] == 0 或 1.
graph[i][j] == graph[j][i]
graph[i][i] == 1
1 <= initial.length <= n
0 <= initial[i] <= n - 1
initial 中所有整数均不重复
*/

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        int m = initial.size();
        // 删除的节点
        bool is_delete[m];
        memset(is_delete, 0, sizeof(is_delete));
        // 被感染的节点
        bool is_tran[n];
        memset(is_tran, 0, sizeof(is_tran));

        function<void(int)> dfs = [&](int i) {
            for (int j = 0; j < n; ++j) {
                if (!is_tran[j] && graph[i][j]) {  // 没感染有连接，则感染
                    is_tran[j] = true;
                    dfs(j);
                }
            }
        };

        sort(initial.begin(), initial.end());  // 要返回索引最小的节点
        int index = initial[0], minfnode = n;
        for (int i = 0; i < m; ++i) {
            if (is_delete[i])
                continue;
            // 初始化is_delete
            is_delete[i] = true;  // 删除i节点
            for (int j = i; j < m; ++j) {
                if (!is_delete[j] && graph[initial[i]][initial[j]])
                    is_delete[j] = true;  // j未删但连接了等于删了
            }

            // 开始感染
            memset(is_tran, 0, sizeof(is_tran));
            for (int j = 0; j < m; ++j) {
                if (i == j)
                    continue;     // 不感染
                dfs(initial[j]);  // 感染
            }

            // 记录感染的数量
            int fnode = 0;
            for (int i = 0; i < n; ++i) {
                if (is_tran[i])
                    fnode++;
            }

            // 更新最小感染节点数，最小索引，不能=否则最大索引
            if (fnode < minfnode) {
                minfnode = fnode;
                index = initial[i];
            }
        }
        return index;
    }
};

int main() {
    Solution s;
    vector<vector<int>> graph = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    vector<int> initial = {0, 1};
    cout << s.minMalwareSpread(graph, initial) << endl;

    graph = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    initial = {0, 2};
    cout << s.minMalwareSpread(graph, initial) << endl;

    graph = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    initial = {1, 2};
    cout << s.minMalwareSpread(graph, initial) << endl;
    return 0;
}