/*
20230827 写出自己的SharedPointer实现
在这个实现中，我们使用了一个指向计数器的指针来记录有多少个shared pointer共享同一个对象。
每当创建一个shared pointer时，我们将计数器初始化为1；
每当复制一个shared pointer时，我们将计数器加1；
每当销毁一个shared pointer时，我们将计数器减1。当计数器变为0时，我们释放所管理的对象的内存。
这样，我们就可以实现一个智能指针，它可以自动管理对象的生命周期，避免内存泄漏和悬空指针等问题。
*/

#include <iostream>

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* ptr = nullptr) : m_ptr(ptr), m_count(new size_t(1)) {}

    SharedPointer(const SharedPointer& sp) : m_ptr(sp.m_ptr), m_count(sp.m_count) {
        ++(*m_count);
    }

    ~SharedPointer() {
        if (--(*m_count) == 0) {
            delete m_ptr;
            delete m_count;
        }
    }

    SharedPointer& operator=(const SharedPointer& sp) {
        if (this != &sp) {
            if (--(*m_count) == 0) {
                delete m_ptr;
                delete m_count;
            }
            m_ptr = sp.m_ptr;
            m_count = sp.m_count;
            ++(*m_count);
        }
        return *this;
    }

    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

private:
    T* m_ptr;
    size_t* m_count;
};

int main() {
    SharedPointer<int> sp1(new int(42));
    SharedPointer<int> sp2 = sp1;
    std::cout << *sp1 << std::endl; // 输出 42
    std::cout << *sp2 << std::endl; // 输出 42
    return 0;
}

