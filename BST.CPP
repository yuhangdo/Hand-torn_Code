//20230827 面试遇到的手撕二叉搜索树，要求如下
//1、使用类模板实现
//2、实现一个函数，给定vector数组，构造一个二叉搜素树
//3、实现二叉搜索树的后序遍历

//首先，我们需要定义一个二叉搜索树的节点结构体，包含整数值、左子节点指针和右子节点指针。然后，我们实现一个二叉搜索树类，包含插入、查找、后序遍历等方法。

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T x) : val(x), left(NULL), right(NULL) {}
};

template <typename T>
class BST {
public:
    BST() : root(NULL) {}

    void insert(T val) {
        if (root == NULL) {
            root = new TreeNode<T>(val);
        } else {
            insert(root, val);
        }
    }

    bool find(T val) {
        return find(root, val);
    }

    void postorderTraversal() {
        postorderTraversal(root);
        std::cout << std::endl;
    }

private:
    TreeNode<T>* root;

    void insert(TreeNode<T>* node, T val) {
        if (val < node->val) {
            if (node->left == NULL) {
                node->left = new TreeNode<T>(val);
            } else {
                insert(node->left, val);
            }
        } else {
            if (node->right == NULL) {
                node->right = new TreeNode<T>(val);
            } else {
                insert(node->right, val);
            }
        }
    }

    bool find(TreeNode<T>* node, T val) {
        if (node == NULL) {
            return false;
        }
        if (val == node->val) {
            return true;
        } else if (val < node->val) {
            return find(node->left, val);
        } else {
            return find(node->right, val);
        }
    }

    void postorderTraversal(TreeNode<T>* node) {
        if (node == NULL) {
            return;
        }
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->val << " ";
    }
};

int main() {
    vector<int> arr = {5, 3, 7, 2, 4, 6, 8};
    BST<int> bst;
    for (int i = 0; i < arr.size(); i++) {
        bst.insert(arr[i]);
    }
    bst.postorderTraversal(); // 输出：2 4 3 6 8 5 7

    return 0;
}
