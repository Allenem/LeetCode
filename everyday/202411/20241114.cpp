/*
3249. 统计好节点的数目

现有一棵 无向 树，树中包含 n 个节点，按从 0 到 n - 1 标记。树的根节点是节点 0 。给你一个长度为 n - 1 的二维整数数组 edges，其中 edges[i] = [ai, bi] 表示树中节点 ai 与节点 bi 之间存在一条边。

如果一个节点的所有子节点为根的 子树 包含的节点数相同，则认为该节点是一个 好节点。

返回给定树中 好节点 的数量。

子树 指的是一个节点以及它所有后代节点构成的一棵树。



示例 1：

输入：edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]

输出：7

说明：
  
                    0
                /       \
             1             2
           /   \         /   \
          3      4      5     6

树的所有节点都是好节点。



示例 2：

输入：edges = [[0,1],[1,2],[2,3],[3,4],[0,5],[1,6],[2,7],[3,8]]

输出：6

说明：

                0
              /  \
             1   [5]
           /   \            
          2    [6]        
         / \      
        [3] [7]
       /  \
      [4] [8]

树中有 6 个好节点。上图中已将这些节点着色。



示例 3：

输入：edges = [[0,1],[1,2],[1,3],[1,4],[0,5],[5,6],[6,7],[7,8],[0,9],[9,10],[9,12],[10,11]]

输出：12

解释：

                 0
              /  |  \
             1   5   9
            /|\   |   |\
           2 3 4  6   10 12 
                  |   |
                  7   11
                  |
                  8

除了节点 9 以外其他所有节点都是好节点。

 

提示：

2 <= n <= 105
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
输入确保 edges 总表示一棵有效的树。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for(auto& e:edges){
            int x = e[0], y = e[1];
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = 0;
        auto dfs = [&](auto&& dfs, int x, int fa) -> int {
            int szx = 1, sz0 = 0;
            bool ok = true;
            for(int y:g[x]){
                if(y==fa) continue; // 跳过父节点
                int szy = dfs(dfs, y, x);
                if(sz0 == 0) sz0 = szy; // 记录第一个子树大小
                else if(szy != sz0) ok = false; // 注意不能 break，其他子树 y 仍然要递归
                szx += szy;
            }
            ans += ok;
            return szx;
        };

        dfs(dfs, 0, -1);
        return ans;
    }
};

int main(){
    Solution s;
    vector<vector<int>> edges = {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}};
    cout << s.countGoodNodes(edges) << endl; // 7

    edges = {{0,1},{1,2},{2,3},{3,4},{0,5},{1,6},{2,7},{3,8}};
    cout << s.countGoodNodes(edges) << endl; // 6

    edges = {{0,1},{1,2},{1,3},{1,4},{0,5},{5,6},{6,7},{7,8},{0,9},{9,10},{9,12},{10,11}};
    cout << s.countGoodNodes(edges) << endl; // 12

    return 0;
}