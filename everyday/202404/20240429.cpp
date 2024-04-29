/*
1329. 将矩阵按对角线排序

矩阵对角线 是一条从矩阵最上面行或者最左侧列中的某个元素开始的对角线，沿右下方向一直到矩阵末尾的元素。例如，矩阵 mat 有 6 行 3 列，从 mat[2][0] 开始的 矩阵对角线 将会经过 mat[2][0]、mat[3][1] 和 mat[4][2] 。

给你一个 m * n 的整数矩阵 mat ，请你将同一条 矩阵对角线 上的元素按升序排序后，返回排好序的矩阵。

示例 1：

3  3  1  1      1  1  1  1
 ↘  ↘  ↘         ↘  ↘  ↘
2  2  1  2  ->  1  2  2  2
 ↘  ↘  ↘        ↘  ↘  ↘
1  1  1  2      1  2  3  3

输入：mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
输出：[[1,1,1,1],[1,2,2,2],[1,2,3,3]]

示例 2：

输入：mat = [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
输出：[[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
 

提示：

m == mat.length
n == mat[i].length
1 <= m, n <= 100
1 <= mat[i][j] <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m=mat.size(),n=mat[0].size();
        function<void(int,int)> help=[&](int i, int j){
            vector<int> tmp;
            int x=i,y=j;
            while(x<m&&y<n)tmp.push_back(mat[x++][y++]);
            sort(tmp.begin(),tmp.end());
            x=i,y=j;
            int z=0;
            while(x<m&&y<n)mat[x++][y++]=tmp[z++];
        };
        for(int i=0;i<m;++i) help(i,0);
        for(int j=1;j<n;++j) help(0,j);
        return mat;
    }
};


int main() {
    Solution solution;
    vector<vector<int>> mat = {{3,3,1,1},{2,2,1,2},{1,1,1,2}};
    vector<vector<int>> ans = solution.diagonalSort(mat);
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    mat = {{11,25,66,1,69,7},{23,55,17,45,15,52},{75,31,36,44,58,8},{22,27,33,25,68,4},{84,28,14,11,5,50}};
    ans = solution.diagonalSort(mat);
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}