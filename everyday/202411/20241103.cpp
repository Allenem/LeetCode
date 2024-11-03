/*
638. 大礼包

在 LeetCode 商店中， 有 n 件在售的物品。每件物品都有对应的价格。然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。

给你一个整数数组 price 表示物品价格，其中 price[i] 是第 i 件物品的价格。另有一个整数数组 needs 表示购物清单，其中 needs[i] 是需要购买第 i 件物品的数量。

还有一个数组 special 表示大礼包，special[i] 的长度为 n + 1 ，其中 special[i][j] 表示第 i 个大礼包中内含第 j 件物品的数量，且 special[i][n] （也就是数组中的最后一个整数）为第 i 个大礼包的价格。

返回 确切 满足购物清单所需花费的最低价格，你可以充分利用大礼包的优惠活动。你不能购买超出购物清单指定数量的物品，即使那样会降低整体价格。任意大礼包可无限次购买。


示例 1：

输入：price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
输出：14
解释：有 A 和 B 两种物品，价格分别为 ¥2 和 ¥5 。 
大礼包 1 ，你可以以 ¥5 的价格购买 3A 和 0B 。 
大礼包 2 ，你可以以 ¥10 的价格购买 1A 和 2B 。 
需要购买 3 个 A 和 2 个 B ， 所以付 ¥10 购买 1A 和 2B（大礼包 2），以及 ¥4 购买 2A 。


示例 2：

输入：price = [2,3,4], special = [[1,1,0,4],[2,2,1,9]], needs = [1,2,1]
输出：11
解释：A ，B ，C 的价格分别为 ¥2 ，¥3 ，¥4 。
可以用 ¥4 购买 1A 和 1B ，也可以用 ¥9 购买 2A ，2B 和 1C 。 
需要买 1A ，2B 和 1C ，所以付 ¥4 买 1A 和 1B（大礼包 1），以及 ¥3 购买 1B ， ¥4 购买 1C 。 
不可以购买超出待购清单的物品，尽管购买大礼包 2 更加便宜。
 

提示：

n == price.length == needs.length
1 <= n <= 6
0 <= price[i], needs[i] <= 10
1 <= special.length <= 100
special[i].length == n + 1
0 <= special[i][j] <= 50
生成的输入对于 0 <= j <= n - 1 至少有一个 special[i][j] 非零。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int ans = INT_MAX;
    vector<int>buy;
    void trackback(vector<int>& price, vector<vector<int>>& special, vector<int>& needs, int money, int index) {
        if (index == special.size()) {//当遍历完大礼包数组时，判断当前选择是否更优惠
            int extra = 0;
            for (int i = 0; i < needs.size(); i++) {//将buy数组补到与needs数组相同
                extra += (needs[i] - buy[i]) * price[i];
            }
            ans = min(ans, money + extra);
            return;
        }
        for (int i = index; i <= special.size(); i++) {
            int j = 0;
            for (; j < needs.size() && i < special.size(); j++) {//判断该大礼包是否可选，当不会多买时，便可选
                if (buy[j] + special[i][j] > needs[j]) {
                    break;
                }
            }
            if (j == needs.size() || i == special.size()) {
                for (int j = 0; j < needs.size() && i < special.size(); j++) {//买入special[i][j]个j
                    buy[j] += special[i][j];
                }
                if(i < special.size()) money += special[i][needs.size()];//花钱special[i][needs.size()]买下该大礼包
                trackback(price, special, needs, money, i);//递归
                for (int j = 0; j < needs.size() && i < special.size(); j++) {//回溯退货
                    buy[j] -= special[i][j];
                }
                if (i < special.size()) money -= special[i][needs.size()];//回溯退款
            }
        }
    }
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        buy.resize(needs.size(), 0);
        trackback(price, special, needs, 0, 0);
        return ans;
    }
};

// 作者：hoboom
// 链接：https://leetcode.cn/problems/shopping-offers/solutions/1063649/chui-su-fa-by-hoboom-u80h/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution sol;
    vector<int> price = {2, 5};
    vector<vector<int>> special = {{3, 0, 5}, {1, 2, 10}};
    vector<int> needs = {3, 2};
    cout << sol.shoppingOffers(price, special, needs) << endl;

    price = {2, 3, 4};
    special = {{1, 1, 0, 4}, {2, 2, 1, 9}};
    needs = {1, 2, 1};
    cout << sol.shoppingOffers(price, special, needs) << endl;
    
    return 0;
}