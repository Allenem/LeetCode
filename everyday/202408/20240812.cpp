/*
676. 实现一个魔法字典

设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同 。 如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。

实现 MagicDictionary 类：

MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组 dictionary 设定该数据结构，dictionary 中的字符串互不相同
bool search(String searchWord) 给定一个字符串 searchWord ，判定能否只将字符串中 一个 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回 true ；否则，返回 false 。
 

示例：

输入
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
输出
[null, null, false, true, false, false]

解释
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // 返回 False
magicDictionary.search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配 "hello" ，所以返回 True
magicDictionary.search("hell"); // 返回 False
magicDictionary.search("leetcoded"); // 返回 False
 

提示：

1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i] 仅由小写英文字母组成
dictionary 中的所有字符串 互不相同
1 <= searchWord.length <= 100
searchWord 仅由小写英文字母组成
buildDict 仅在 search 之前调用一次
最多调用 100 次 search
*/

#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

class Trie {
private:
    Trie* children[26];
    bool isEnd = false;

public:
    Trie() {
        fill(begin(children), end(children), nullptr);
    }

    void insert(const string& w) {
        Trie* node = this;
        for(char c:w) {
            int i = c - 'a';
            if(!node->children[i]) node->children[i] = new Trie();
            node = node->children[i];
        }
        node->isEnd = true;
    }

    bool search(const string& w) {
        function<bool(int, int, Trie*)> dfs = [&](int i, int limit, Trie* node) {
            if(limit < 0) return false;
            if(i >= w.size()) return limit == 0 && node->isEnd;
            int j = w[i] - 'a';
            for(int k = 0; k < 26; k++) {
                if(!node->children[k]) continue;
                if(dfs(i+1, j==k?limit:limit-1, node->children[k])) return true;
            }
            return false;
        };
        return dfs(0, 1, this);
    }
};


class MagicDictionary {
public:
    MagicDictionary() {
        trie = new Trie();
    }
    
    void buildDict(vector<string> dictionary) {
        for (auto& w : dictionary) {
            trie->insert(w);
        }
    }
    
    bool search(string searchWord) {
        return trie->search(searchWord);
    }

private:
    Trie* trie;
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

int main() {
    MagicDictionary* obj = new MagicDictionary();
    obj->buildDict({"hello", "leetcode"});
    cout << boolalpha; 
    cout << obj->search("hello") << endl;
    cout << obj->search("hhllo") << endl;
    cout << obj->search("hell") << endl;
    cout << obj->search("leetcoded") << endl;
    return 0;
}