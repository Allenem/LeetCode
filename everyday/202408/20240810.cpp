/*
2940. 找到 Alice 和 Bob 可以相遇的建筑

给你一个下标从 0 开始的正整数数组 heights ，其中 heights[i] 表示第 i 栋建筑的高度。

如果一个人在建筑 i ，且存在 i < j 的建筑 j 满足 heights[i] < heights[j] ，那么这个人可以移动到建筑 j 。

给你另外一个数组 queries ，其中 queries[i] = [ai, bi] 。第 i 个查询中，Alice 在建筑 ai ，Bob 在建筑 bi 。

请你能返回一个数组 ans ，其中 ans[i] 是第 i 个查询中，Alice 和 Bob 可以相遇的 最左边的建筑 。如果对于查询 i ，Alice 和 Bob 不能相遇，令 ans[i] 为 -1 。


示例 1：

输入：heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
输出：[2,5,-1,5,2]
解释：第一个查询中，Alice 和 Bob 可以移动到建筑 2 ，因为 heights[0] < heights[2] 且 heights[1] < heights[2] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[0] < heights[5] 且 heights[3] < heights[5] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Alice 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[3] < heights[5] 且 heights[4] < heights[5] 。
第五个查询中，Alice 和 Bob 已经在同一栋建筑中。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。


示例 2：

输入：heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
输出：[7,6,-1,4,6]
解释：第一个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[0] < heights[7] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 6 ，因为 heights[3] < heights[6] 且 heights[5] < heights[6] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Bob 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 4 ，因为 heights[3] < heights[4] 且 heights[0] < heights[4] 。
第五个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[1] < heights[6] 。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。
 

提示：

1 <= heights.length <= 5 * 104
1 <= heights[i] <= 109
1 <= queries.length <= 5 * 104
queries[i] = [ai, bi]
0 <= ai, bi <= heights.length - 1
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;


class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        
        int m=heights.size(), n=queries.size();
        stack<int> stk; // 单调不增栈
        vector<int> ngei(m,-1); // >=idx
        
        for(int i=0;i<m;i++){
            while(!stk.empty() && heights[i] > heights[stk.top()]){
                ngei[stk.top()]=i;
                stk.pop();
            }
            stk.push(i);
        }
        
        vector<int> ans(n,-1);
        for(int j=0;j<n;j++){
            int a=queries[j][0],b=queries[j][1];
            if(a==b) ans[j]=a;
            else{
                if(a>b)swap(a,b);
                if(heights[a]<heights[b]) ans[j]=b;
                else if(ngei[a]!=-1&&ngei[b]!=-1){
                    // hs(ng(a))>hs(a)>=hs(b)
                    if(ngei[a]>=b) ans[j]=ngei[a];
                    else{
                        int id=ngei[b];
                        while(id<m && heights[a]>=heights[id])id++;
                        if(id<m) ans[j]=id;
                    }
                }
            }
        }
        
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> heights={6,4,8,5,2,7};
    vector<vector<int>> queries={{0,1},{0,3},{2,4},{3,4},{2,2}};
    vector<int> ans=s.leftmostBuildingQueries(heights,queries);
    for(auto x:ans) cout<<x<<",";
    cout<<endl;

    heights={5,3,8,2,6,1,4,6};
    queries={{0,7},{3,5},{5,2},{3,0},{1,6}};
    ans=s.leftmostBuildingQueries(heights,queries);
    for(auto x:ans) cout<<x<<",";
    cout<<endl;
    
    return 0;
}