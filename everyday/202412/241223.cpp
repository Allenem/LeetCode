/*
855. 考场就座

在考场里，有 n 个座位排成一行，编号为 0 到 n - 1。

当学生进入考场后，他必须坐在离最近的人最远的座位上。如果有多个这样的座位，他会坐在编号最小的座位上。(另外，如果考场里没有人，那么学生就坐在 0 号座位上。)

设计一个模拟所述考场的类。

实现 ExamRoom 类：

ExamRoom(int n) 用座位的数量 n 初始化考场对象。
int seat() 返回下一个学生将会入座的座位编号。
void leave(int p) 指定坐在座位 p 的学生将离开教室。保证座位 p 上会有一位学生。
 

示例 1：

输入：
["ExamRoom", "seat", "seat", "seat", "seat", "leave", "seat"]
[[10], [], [], [], [], [4], []]
输出：
[null, 0, 9, 4, 2, null, 5]
解释：
ExamRoom examRoom = new ExamRoom(10);
examRoom.seat(); // 返回 0，房间里没有人，学生坐在 0 号座位。
examRoom.seat(); // 返回 9，学生最后坐在 9 号座位。
examRoom.seat(); // 返回 4，学生最后坐在 4 号座位。
examRoom.seat(); // 返回 2，学生最后坐在 2 号座位。
examRoom.leave(4);
examRoom.seat(); // 返回 5，学生最后坐在 5 号座位。
 

提示：

1 <= n <= 109
保证有学生正坐在座位 p 上。
seat 和 leave 最多被调用 104 次。
*/
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

int N;

// 计算两个座位之间的距离：
// 如果区间包含边界 (-1 或 N)，则返回区间的实际长度 - 1。
// 否则，返回区间长度的一半，用于找到离中心最近的座位。
int dist(const pair<int, int>& p) {
    auto [l, r] = p;
    if(l == -1 || r == N) return r - l - 1;
    return (r - l) >> 1;
}

// 定义一个比较器 cmp，用于排序区间：
// 优先选择距离更大的区间；
// 如果距离相同，则选择起点较小的区间。
struct cmp {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
        int d1 = dist(a), d2 = dist(b);
        return d1 == d2 ? a.first < b.first : d1 > d2;
    };
};

class ExamRoom {

// 使用数据结构：
// 1. ts：存储所有区间，按距离和起点排序。
// 2. left 和 right：分别记录区间的左边界和右边界，用于快速查找相邻区间。
// add() 和 del() 用于管理区间的插入和删除。
private:
    set<pair<int, int>, cmp> ts;
    unordered_map<int, int> left;
    unordered_map<int, int> right;
    int n;

    void add(pair<int, int> s) {
        ts.insert(s);
        left[s.second] = s.first;
        right[s.first] = s.second;
    }

    void del(pair<int, int> s) {
        ts.erase(s);
        left.erase(s.second);
        right.erase(s.first);
    }

public:
    // 初始化考场，n 为座位总数。
    // 初始时整个座位范围是 (-1, n)，即没有人坐。
    ExamRoom(int n) {
        N = n;
        this->n = n;
        add({-1, n});
    }
    
    // 分配座位：
    // 从区间集合中找到距离最大的区间。
    // 计算新座位 p：为区间的中点。
    // 如果区间起点是 -1，选择座位 0；如果终点是 n，选择座位 n-1。
    // 更新区间集合，删除原区间并添加两个新区间。
    // 返回新座位 p。
    int seat() {
        auto s = *ts.begin();
        int p = (s.first + s.second) >> 1;
        if(s.first == -1) p = 0;
        else if(s.second == n) p = n - 1;
        del(s);
        add({s.first, p});
        add({p, s.second});
        return p;
    }
    
    // 离开座位：
    // 找到座位 p 左右相邻的座位。
    // 删除对应的两个区间。
    // 合并为一个新区间并加入集合。
    void leave(int p) {
        int l = left[p], r = right[p];
        del({l, p});
        del({p, r});
        add({l, r});
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */

int main() {
    ExamRoom* obj = new ExamRoom(10);
    cout << obj->seat() << endl;
    cout << obj->seat() << endl;
    cout << obj->seat() << endl;
    cout << obj->seat() << endl;
    obj->leave(4);
    cout << obj->seat() << endl;
    return 0;
}