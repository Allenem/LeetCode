/*
2181. 合并零之间的节点

给你一个链表的头节点 head ，该链表包含由 0 分隔开的一连串整数。链表的 开端 和 末尾 的节点都满足 Node.val == 0 。

对于每两个相邻的 0 ，请你将它们之间的所有节点合并成一个节点，其值是所有已合并节点的值之和。然后将所有 0 移除，修改后的链表不应该含有任何 0 。

返回修改后链表的头节点 head 。


示例 1：

(0) -> 3 -> 1 -> (0) -> 4 -> 5 -> 2 -> (0)
4 -> 11

输入：head = [0,3,1,0,4,5,2,0]
输出：[4,11]
解释：
上图表示输入的链表。修改后的链表包含：
- 标记为绿色的节点之和：3 + 1 = 4
- 标记为红色的节点之和：4 + 5 + 2 = 11


示例 2：

(0) -> 1 -> (0) -> 3 -> (0) -> 2 -> 2 -> (0)
1 -> 3 -> 4

输入：head = [0,1,0,3,0,2,2,0]
输出：[1,3,4]
解释：
上图表示输入的链表。修改后的链表包含：
- 标记为绿色的节点之和：1 = 1
- 标记为红色的节点之和：3 = 3
- 标记为黄色的节点之和：2 + 2 = 4


提示：

列表中的节点数目在范围 [3, 2 * 105] 内
0 <= Node.val <= 1000
不 存在连续两个 Node.val == 0 的节点
链表的 开端 和 末尾 节点都满足 Node.val == 0
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        int presum = 0;
        ListNode dummpy, **p = &dummpy.next, *cur = head->next;
        while(cur){
            if(cur->val==0 && presum!=0){
                *p = new ListNode(presum);
                p = &(*p)->next;
                presum = 0;
            }
            presum += cur->val;
            cur = cur->next;
        }
        return dummpy.next;
    }
};

int main(){
    Solution s;

    ListNode *head = new ListNode(0);
    ListNode *cur = head;
    vector<int> nums = {3,1,0,4,5,2,0};
    for(int i=0; i<nums.size(); i++){
        cur->next = new ListNode(nums[i]);
        cur = cur->next;
    }
    ListNode *res = s.mergeNodes(head);
    while(res){
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;

    ListNode *head2 = new ListNode(0);
    ListNode *cur2 = head2;
    vector<int> nums2 = {1,0,3,0,2,2,0};
    for(int i=0; i<nums2.size(); i++){
        cur2->next = new ListNode(nums2[i]);
        cur2 = cur2->next;
    }
    ListNode *res2 = s.mergeNodes(head2);
    while(res2){
        cout << res2->val << " ";
        res2 = res2->next;
    }
    cout << endl;

    return 0;
}