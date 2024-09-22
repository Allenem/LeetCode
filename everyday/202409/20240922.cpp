/*
997. 找到小镇的法官

小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。

如果小镇法官真的存在，那么：

- 小镇法官不会信任任何人。
- 每个人（除了小镇法官）都信任这位小镇法官。
- 只有一个人同时满足属性 1 和属性 2 。

给你一个数组 trust ，其中 trust[i] = [ai, bi] 表示编号为 ai 的人信任编号为 bi 的人。

如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 -1 。


示例 1：

输入：n = 2, trust = [[1,2]]
输出：2


示例 2：

输入：n = 3, trust = [[1,3],[2,3]]
输出：3


示例 3：

输入：n = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1
 
提示：

1 <= n <= 1000
0 <= trust.length <= 104
trust[i].length == 2
trust 中的所有trust[i] = [ai, bi] 互不相同
ai != bi
1 <= ai, bi <= n
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> t(n+1,0);
        for(auto ti:trust){
            t[ti[0]]--;
            t[ti[1]]++;
        }
        for(int i=1;i<=n;i++)if(t[i]==n-1)return i;
        return -1;
    }
};

int main(){
    Solution s;
    int n = 2;
    vector<vector<int>> trust = {{1,2}};
    cout<<s.findJudge(n,trust)<<endl;
    
    n = 3;
    trust = {{1,3},{2,3}};
    cout<<s.findJudge(n,trust)<<endl;

    n = 3;
    trust = {{1,3},{2,3},{3,1}};
    cout<<s.findJudge(n,trust)<<endl;

    return 0;
}