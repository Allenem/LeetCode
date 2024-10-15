/*
3200. 三角形的最大高度

给你两个整数 red 和 blue，分别表示红色球和蓝色球的数量。你需要使用这些球来组成一个三角形，满足第 1 行有 1 个球，第 2 行有 2 个球，第 3 行有 3 个球，依此类推。

每一行的球必须是 相同 颜色，且相邻行的颜色必须 不同。

返回可以实现的三角形的 最大 高度。



示例 1：

输入： red = 2, blue = 4

输出： 3

解释：

    B
  R   R
B   B   B

上图显示了唯一可能的排列方式。



示例 2：

输入： red = 2, blue = 1

输出： 2

解释：

    B
  R   R

上图显示了唯一可能的排列方式。



示例 3：

输入： red = 1, blue = 1

输出： 1



示例 4：

输入： red = 10, blue = 1

输出： 2

解释：

    B
  R   R

上图显示了唯一可能的排列方式。



提示：

1 <= red, blue <= 100
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        return max(find(red,blue),find(blue,red));
    }
    int find(int a, int b){
        for(int i=1;;i++){
            if(i%2==0){
                if(a<i)return i-1;
                a-=i;
            }else{
                if(b<i)return i-1;
                b-=i;
            }
        }
    }
};

int main(){
    Solution s;
    cout<<s.maxHeightOfTriangle(2,4)<<endl;
    cout<<s.maxHeightOfTriangle(2,1)<<endl;
    cout<<s.maxHeightOfTriangle(1,1)<<endl;
    cout<<s.maxHeightOfTriangle(10,1)<<endl;
    return 0;
}