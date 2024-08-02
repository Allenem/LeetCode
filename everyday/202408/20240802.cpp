/*
3128. 直角三角形

给你一个二维 boolean 矩阵 grid 。

请你返回使用 grid 中的 3 个元素可以构建的 直角三角形 数目，且满足 3 个元素值 都 为 1 。

注意：

如果 grid 中 3 个元素满足：一个元素与另一个元素在 同一行，同时与第三个元素在 同一列 ，那么这 3 个元素称为一个 直角三角形 。这 3 个元素互相之间不需要相邻。



示例 1：

0	1	0
0	1	1
0	1	0
0	1	0
0	1	1
0	1	0

输入：grid = [[0,1,0],[0,1,1],[0,1,0]]

输出：2

解释：

有 2 个直角三角形。



示例 2：

1	0	0	0
0	1	0	1
1	0	0	0

输入：grid = [[1,0,0,0],[0,1,0,1],[1,0,0,0]]

输出：0

解释：

没有直角三角形。



示例 3：

1	0	1
1	0	0
1	0	0
1	0	1
1	0	0
1	0	0

输入：grid = [[1,0,1],[1,0,0],[1,0,0]]

输出：2

解释：

有两个直角三角形。



提示：

1 <= grid.length <= 1000
1 <= grid[i].length <= 1000
0 <= grid[i][j] <= 1
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 注意这里初始化-1，是为了后面 [当grid[i][j]==1时，(x[i]-1)*(y[j]-1)] 则中括号内可以直接转化为内积运算，很妙！！！
        vector<int> x(m, -1), y(n, -1); 
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j]) x[i]++, y[j]++;
            }
        }

        long long ans = 0;
        for(int i = 0; i < m; i++){
            // 注意这里的一句，等价于：for i for j if grid[i][j]: ans += (x[i]-1)(y[j]-1)
            if(x[i] > 0) ans += x[i] * inner_product(y.begin(), y.end(), grid[i].begin(), 0ll);
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<vector<int>> grid = {{0,1,0},{0,1,1},{0,1,0}};
    cout << s.numberOfRightTriangles(grid) << endl;

    grid = {{1,0,0,0},{0,1,0,1},{1,0,0,0}};
    cout << s.numberOfRightTriangles(grid) << endl;

    grid = {{1,0,1},{1,0,0},{1,0,0}};
    cout << s.numberOfRightTriangles(grid) << endl;

    return 0;
}