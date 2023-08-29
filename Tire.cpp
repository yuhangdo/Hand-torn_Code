//20230829 实现Tire（前缀树）
//Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
//这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
//Trie 本质上是一颗多叉树

/*
 *
 *实现 Trie 类
 *void insert(String word) 向前缀树中插入字符串 word 。
 *boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
 *boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
 *
 */

class Trie {
public:
    struct Node {
        Node* son[26];
        bool is_end;

        Node() {
            is_end = false;
            for (int i = 0; i < 26; i++) son[i] = nullptr;
        }
    } *root;

    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        auto p = root;
        for (auto & c : word) {
            if (!p->son[c - 'a']) p->son[c - 'a'] = new Node();
            p = p->son[c - 'a']; 
        }
        p->is_end = true;
    }

    bool search(string word) {
        auto p = root;
        for (auto & c : word) {
            if (!p->son[c - 'a']) return false;
            p = p->son[c - 'a'];
        } 
        return p->is_end;
    }

    bool startsWith(string prefix) {
        auto p = root;
        for (auto & c : prefix) {
            if (!p->son[c - 'a']) return false;
            p = p->son[c - 'a'];
        }
        return true;
    }
};

