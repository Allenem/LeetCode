/*
331. 验证二叉树的前序序列化

序列化二叉树的一种方法是使用 前序遍历
。当我们遇到一个非空节点时，我们可以记录下这个节点的值。如果它是一个空节点，我们可以使用一个标记值记录，例如
#。

         _9_
        /   \
     3     2
    / \   / \
    4   1  #  6
例如，上面的二叉树可以被序列化为字符串 "9,3,4,#,#,1,#,#,2,#,6,#,#"，其中 #
代表一个空节点。

给定一串以逗号分隔的序列，验证它是否是正确的二叉树的前序序列化。编写一个在不重构树的条件下的可行算法。

保证 每个以逗号分隔的字符或为一个整数或为一个表示 null 指针的 '#' 。

你可以认为输入格式总是有效的

例如它永远不会包含两个连续的逗号，比如 "1,,3" 。

注意：不允许重建树。

示例 1:

输入: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
输出: true

示例 2:

输入: preorder = "1,#"
输出: false

示例 3:

输入: preorder = "9,#,#,1"
输出: false

提示:

1 <= preorder.length <= 104
preorder 由以逗号 “，” 分隔的 [0,100] 范围内的整数和 “#” 组成
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValidSerialization(string preorder) {
        int n = preorder.size();
        int num = 0;  // 记录#的个数
        for (int i = n - 1; i > -1; i--) {
            if (preorder[i] == ',')
                continue;
            if (preorder[i] == '#')
                num++;
            else {
                while (i >= 0 && preorder[i] != ',')  // 节点数字可能有多位
                    i--;
                if (num >=
                    2)  // #的个数>=2，消除2个#，消除一个节点数字并转换成#，即num-1
                    num--;
                else
                    return false;  // #的个数不足2，证明false
            }
        }
        return num == 1 ? true : false;  // 最终#的个数须==1
    }
};

int main() {
    Solution sol;
    cout << sol.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") << endl;
    cout << sol.isValidSerialization("1,#") << endl;
    cout << sol.isValidSerialization("9,#,#,1") << endl;
    return 0;
}