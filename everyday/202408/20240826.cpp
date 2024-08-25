/*
690. 员工的重要性

你有一个保存员工信息的数据结构，它包含了员工唯一的 id ，重要度和直系下属的 id 。

给定一个员工数组 employees，其中：

employees[i].id 是第 i 个员工的 ID。
employees[i].importance 是第 i 个员工的重要度。
employees[i].subordinates 是第 i 名员工的直接下属的 ID 列表。
给定一个整数 id 表示一个员工的 ID，返回这个员工和他所有下属的重要度的 总和。

 

示例 1：

                    ----------------
                    |    ID = 1    |
                    | importance=5 |
                    ----------------
                    /               \
                   /                 \
                  /                   \
        ----------------        ----------------
        |    ID = 2    |        |    ID = 3    |
        | importance=3 |        | importance=3 |
        ----------------        ----------------
                  

输入：employees = [[1,5,[2,3]],[2,3,[]],[3,3,[]]], id = 1
输出：11
解释：
员工 1 自身的重要度是 5 ，他有两个直系下属 2 和 3 ，而且 2 和 3 的重要度均为 3 。因此员工 1 的总重要度是 5 + 3 + 3 = 11 。
 

示例 2：

                    ----------------
                    |    ID = 1    |
                    | importance=2 |
                    ----------------
                    /               
                   /                 
                  /                   
        ----------------        
        |    ID = 5    |        
        |importance=-3 |        
        ----------------        


输入：employees = [[1,2,[5]],[5,-3,[]]], id = 5
输出：-3
解释：员工 5 的重要度为 -3 并且没有直接下属。
因此，员工 5 的总重要度为 -3。
 

提示：

1 <= employees.length <= 2000
1 <= employees[i].id <= 2000
所有的 employees[i].id 互不相同。
-100 <= employees[i].importance <= 100
一名员工最多有一名直接领导，并可能有多名下属。
employees[i].subordinates 中的 ID 都有效。
*/
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        function<int(int)> dfs = [&](int idx) -> int {
            int cur = 0;
            for(int i = 0; i < employees.size(); i++){
                if(employees[i]->id == idx){
                    cur += employees[i]->importance;
                    if(!(employees[i]->subordinates).empty()){
                        for(int sonid:employees[i]->subordinates){
                            cur += dfs(sonid);
                        }
                    }
                    // cout<<idx<<" "<<cur<<endl;
                    break;
                }
            }
            return cur;
        };
        return dfs(id);
    }
};

int main(){
    Solution s;

    vector<Employee*> employees;
    Employee* e1 = new Employee();
    e1->id = 1;
    e1->importance = 5;
    e1->subordinates = {2,3};
    employees.push_back(e1);
    Employee* e2 = new Employee();
    e2->id = 2;
    e2->importance = 3;
    e2->subordinates = {};
    employees.push_back(e2);
    Employee* e3 = new Employee();
    e3->id = 3;
    e3->importance = 3;
    e3->subordinates = {};
    employees.push_back(e3);
    cout<<s.getImportance(employees, 1)<<endl;


    vector<Employee*> employees2;
    Employee* e4 = new Employee();
    e4->id = 1;
    e4->importance = 2;
    e4->subordinates = {5};
    employees2.push_back(e4);
    Employee* e5 = new Employee();
    e5->id = 5;
    e5->importance = -3;
    e5->subordinates = {};
    employees2.push_back(e5);
    cout<<s.getImportance(employees2, 5)<<endl;

    return 0;
}