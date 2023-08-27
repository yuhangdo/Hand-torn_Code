//20230827 实现LRU缓存策略
/*
 * 
 *实现 LRUCache 类：
 *LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
 *int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
 *void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
 *函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
 *
 */

//tip:简单实现

class LRUCache {
public:
    struct Node {
        int key;
        int val;
        Node* left;
        Node* right;
        Node(int _key, int _val) : key(_key), val(_val), left(nullptr), right(nullptr) {}
    };

    LRUCache(int capacity) {
        n = capacity;
        L = new Node(-1, -1);
        R = new Node(-1, -1);
        L->right = R;
        R->left = L;
    }

    int get(int key) {
        if (use.count(key)) {
…           auto t = new Node(key, value);
            use[key] = t;
            insert(t);
        }
    }

    void put(int key, int value) {
        if (use.count(key)) {
	    use[key]->val = value;
            remove(use[key]);
            insert(use[key]);
	}…else {
	    if (use.size() == n) {
                auto p = R->left;
                remove(p);
                use.erase(p->key);
                delete(p);
            }
	    auto t = new Node(key, value);
	    use[key] = t;
	    insert(t);	
        }
    }

private:
    int n;
    Node* L;
    Node* R;
    unordered_map<int, Node*> use;
    
    void remove(Node* p) {
    	p->left->right = p->right;
        p->right->left = p->left;
    }     

    void insert(Node* p) {
	p->right = L->right;
        L->right->left = p;
        p->left = L;
        L->right = p;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


