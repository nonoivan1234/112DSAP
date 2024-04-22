#include <utility>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

// 模板參數 T 的合法型態會支援：
// - 值初始化：歸零
// - 複製語意：複製建構與賦值
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string 等等
template<typename T>
struct Node {
    T data;
    Node<T>* parent;
    Node<T>* left{};
    Node<T>* right{};
    explicit Node(const T& data, Node<T>* parent) : data{data}, parent{parent} {}
};

template<typename T>
class BinarySearchTreeSetIterator {
public:
    explicit BinarySearchTreeSetIterator(Node<T>* node) : node_{node} {}
    [[nodiscard]] bool HasNext() const;
    [[nodiscard]] T Next();
private:
    Node<T>* node_;
};

template<typename T>
class BinarySearchTreeSet {
public:
    BinarySearchTreeSet() = default;
    BinarySearchTreeSet(std::initializer_list<T>);
    BinarySearchTreeSet(const BinarySearchTreeSet<T>&) = delete;
    ~BinarySearchTreeSet();
    BinarySearchTreeSet& operator=(const BinarySearchTreeSet<T>&) = delete;
    [[nodiscard]] bool Contains(const T& val) const;
    [[nodiscard]] std::vector<T> Search(const T& lower, const T& upper) const;
    bool Add(const T& val);
    bool Remove(const T& val);
    void Clear();
    [[nodiscard]] BinarySearchTreeSetIterator<T> GetIterator() const;
    [[nodiscard]] size_t Size() const { return size_; }
private:
    Node<T>* root_{};
    size_t size_{};
};

template<typename T>
std::ostream& operator<<(std::ostream&, const BinarySearchTreeSet<T>&);

template<typename T>
std::ostream& operator<<(std::ostream&, const std::vector<T>&);

void Test1(); // Sample1
void Test2(); // Add
void Test3(); // Add, Search
void Test4(); // Add, Clear
void Test5(); // Add, Remove
void Test6(); // Add, GetIterator
void Test7(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7 };
    f[id-1]();
}

namespace Feis { /* HIDDEN */ }

void Test1() {
    // 實作 Add(val) 方法
    // - 如果要新增的值 val 已經存在，則回傳 false，否則回傳 true
    // 實作解構子 ~BinarySearchTreeSet()
    {
        BinarySearchTreeSet<int> a;

        std::cout << std::boolalpha;
        std::cout << "01) " << a.Add(4) << std::endl;
        std::cout << "02) " << a.Add(5) << std::endl;
        std::cout << "03) " << a.Add(3) << std::endl;
        std::cout << "04) " << a.Size() << std::endl;

        std::cout << "05) ";
        for (int i = 1; i <= 5; i++) {
            std::cout << a.Contains(i) << " ";
        }
        std::cout << std::endl;

        std::cout << "06) " << a.Add(5) << std::endl;
        std::cout << "07) " << a.Add(2) << std::endl;
        std::cout << "08) " << a.Size() << std::endl;

        std::cout << "09) ";
        for (int i = 1; i <= 5; i++) {
            std::cout << a.Contains(i) << " ";
        }
        std::cout << std::endl;

        // 01) true
        // 02) true
        // 03) true
        // 04) 3
        // 05) false false true true true
        // 06) false
        // 07) true
        // 08) 4
        // 09) false true true true true
    }

    // 實作建構子 BinarySearchTreeSet(std::initializer_list<T>)
    {
        BinarySearchTreeSet<int> a = {3, 9, 5, 7, 5};
        std::cout << "10) " << a.Size() << std::endl;
        std::cout << "11) ";
        for (int i = 1; i <= 5; i++) {
            std::cout << a.Contains(i) << " ";
        }
        std::cout << std::endl;

        // 10) 4
        // 11) false false true false true
    }

    // 實作 Search(lower, upper) 方法，回傳所有大於等於 lower 且小於等於 upper 的值構成的陣列
    // - 所回傳的陣列內，所有的元素由小到大排序
    {
        BinarySearchTreeSet<int> a = {3, 9, 5, 7, 5};

        std::cout << "16) " << a.Search(3, 5) << std::endl;
        std::cout << "17) " << a.Search(2, 8) << std::endl;

        // 16) {3, 5}
        // 17) {3, 5, 7}
    }

    // 實作 Clear 方法
    {
        BinarySearchTreeSet<int> a = {3, 9, 5};
        std::cout << "18) " << a.Search(1, 10) << std::endl;
        a.Clear();
        std::cout << "19) " << a.Search(1, 10) << std::endl;
        a.Add(9);
        a.Add(1);
        a.Add(3);
        std::cout << "20) " << a.Search(1, 10) << std::endl;

        // 18) {3, 5, 9}
        // 19) {}
        // 20) {1, 3, 9}
    }

    // 實作 Remove(val) 方法，移除值為 val 的元素。
    // - 如果該值存在則刪除該元素並回傳 true
    // - 如果該值不存在則回傳 false，不發生其他影響。
    {
        BinarySearchTreeSet<int> a = {3, 9, 5};

        std::cout << "21) " << a.Remove(3) << std::endl;
        std::cout << "22) " << a.Search(1, 10) << std::endl;
        std::cout << "23) " << a.Remove(3) << std::endl;
        std::cout << "24) " << a.Search(1, 10) << std::endl;
        std::cout << "25) " << a.Remove(5) << std::endl;
        std::cout << "26) " << a.Remove(9) << std::endl;
        std::cout << "27) " << a.Search(1, 10) << std::endl;

        // 21) true
        // 22) {5, 9}
        // 23) false
        // 24) {5, 9}
        // 25) true
        // 26) true
        // 27) {}
    }

    // 實作 GetIterator() 方法，回傳一個 BinarySearchTreeSetIterator 類別的物件，用來迭代集合中所有元素
    // 實作 BinarySearchTreeSetIterator::HasNext() 方法，回傳集合內是否還有下一個元素為迭代到的元素
    // 實作 BinarySearchTreeSetIterator::Next() 方法，回傳集合內下一個元素的值
    // - 集合內元素的迭代順序為由小到大排序
    // - 在 GetIterator() 取得迭代器之後，如果同一個集合又新增或刪除元素的話，原本取得的 Iterator 將會失效，對其再做任何操作都是《未定義行為》
    // - 在新增或刪除元素後，需要使用 GetIterator() 取得迭代器後，從頭開始重新迭代
    {
        BinarySearchTreeSet<int> a = {3, 9, 5};

        BinarySearchTreeSetIterator<int> iter = a.GetIterator();
        std::cout << "28) " << iter.HasNext() << std::endl;
        std::cout << "29) " << iter.Next() << std::endl;
        std::cout << "30) " << iter.Next() << std::endl;
        std::cout << "31) " << iter.Next() << std::endl;
        std::cout << "32) " << iter.HasNext() << std::endl;
        std::cout << "33) " << a << std::endl;

        // 28) true
        // 29) 3
        // 30) 5
        // 31) 9
        // 32) false
        // 33) {3, 5, 9}
    }
}

void Test2() {
      // 實作 GetIterator() 方法，回傳一個 BinarySearchTreeSetIterator 類別的物件，用來迭代集合中所有元素
    // 實作 BinarySearchTreeSetIterator::HasNext() 方法，回傳集合內是否還有下一個元素為迭代到的元素
    // 實作 BinarySearchTreeSetIterator::Next() 方法，回傳集合內下一個元素的值
    // - 集合內元素的迭代順序為由小到大排序
    // - 在 GetIterator() 取得迭代器之後，如果同一個集合又新增或刪除元素的話，原本取得的 Iterator 將會失效，對其再做任何操作都是《未定義行為》
    // - 在新增或刪除元素後，需要使用 GetIterator() 取得迭代器後，從頭開始重新迭代
    {
        BinarySearchTreeSet<int> a = {3, 9, 5};

        BinarySearchTreeSetIterator<int> iter = a.GetIterator();
        std::cout << "28) " << iter.HasNext() << std::endl;
        std::cout << "29) " << iter.Next() << std::endl;
        std::cout << "30) " << iter.Next() << std::endl;
        std::cout << "31) " << iter.Next() << std::endl;
        std::cout << "32) " << iter.HasNext() << std::endl;
        // std::cout << "33) " << a << std::endl;

        // 28) true
        // 29) 3
        // 30) 5
        // 31) 9
        // 32) false
        // 33) {3, 5, 9}
    }
}
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }

namespace {
    template<typename T>
    bool Contains(Node<T>* root, const T& val) {
        if (!root) {
            return false;
        }
        if (val < root->data) {
            return Contains(root->left, val);
        }
        if (root->data < val) {
            return Contains(root->right, val);
        }
        return true;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << '{';
    if (v.size() > 0) {
        os << v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            os << ", " << v[i];
        }
    }
    os << '}';
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTreeSet<T>& s) {
    auto output = s.GetIterator();
    os << '{';
    if (output.HasNext()) {
        os << output.Next();
        while (output.HasNext()) {
            os << ", " << output.Next();
        }
    }
    os << '}';
    return os;
}

template<typename T>
bool BinarySearchTreeSet<T>::Contains(const T& val) const {
    return ::Contains(root_, val);
}

// [YOUR CODE WILL BE PLACED HERE]
template<typename T>
BinarySearchTreeSet<T>::BinarySearchTreeSet(std::initializer_list<T> list) {
    for (const T& val : list) {
        Add(val);
    }
}

template<typename T>
BinarySearchTreeSet<T>::~BinarySearchTreeSet() {
    Clear();
}

template<typename T>
std::vector<T> BinarySearchTreeSet<T>::Search(const T& lower, const T& upper) const {
    std::vector<T> result;
    std::function<void(Node<T>*)> search = [&](Node<T>* node) {
        if (!node) {
            return;
        }
        if (node->data >= lower) {
            search(node->left);
        }
        if (lower <= node->data && node->data <= upper) {
            result.push_back(node->data);
        }
        if (node->data <= upper) {
            search(node->right);
        }
    };
    search(root_);
    return result;
}

template<typename T>
bool BinarySearchTreeSet<T>::Add(const T& val) {
    Node<T>* parent = nullptr;
    Node<T>* current = root_;
    while (current) {
        parent = current;
        if (val < current->data) {
            current = current->left;
        } else if (current->data < val) {
            current = current->right;
        } else {
            return false;
        }
    }
    Node<T>* node = new Node<T>(val, parent);
    if (!parent) {
        root_ = node;
    } else if (val < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    size_++;
    return true;
}

template<typename T>
bool BinarySearchTreeSet<T>::Remove(const T& val) {
    Node<T>* current = root_;
    while (current) {
        if (val < current->data) {
            current = current->left;
        } else if (current->data < val) {
            current = current->right;
        } else {
            break;
        }
    }
    if (!current) {
        return false;
    }
    if (current->left && current->right) {
        Node<T>* successor = current->right;
        while (successor->left) {
            successor = successor->left;
        }
        current->data = successor->data;
        current = successor;
    }
    Node<T>* child = current->left ? current->left : current->right;
    if (current == root_) {
        root_ = child;
    } else if (current->parent->left == current) {
        current->parent->left = child;
    } else {
        current->parent->right = child;
    }
    if (child) {
        child->parent = current->parent;
    }
    delete current;
    size_--;
    return true;
}

template<typename T>
void BinarySearchTreeSet<T>::Clear() {
    std::function<void(Node<T>*)> clear = [&](Node<T>* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    };
    clear(root_);
    root_ = nullptr;
    size_ = 0;
}

template<typename T>
BinarySearchTreeSetIterator<T> BinarySearchTreeSet<T>::GetIterator() const {
    Node<T>* current = root_;
    while (current && current->left) {
        current = current->left;
    }
    return BinarySearchTreeSetIterator<T>(current);
}

template<typename T>
bool BinarySearchTreeSetIterator<T>::HasNext() const {
    return node_ != nullptr;
}

template<typename T>
T BinarySearchTreeSetIterator<T>::Next() {
    Node<T>* nextNode = nullptr;
    
    // If the right child exists, go to the leftmost node of the right subtree
    if (node_->right != nullptr) {
        nextNode = node_->right;
        while (nextNode->left != nullptr) {
            nextNode = nextNode->left;
        }
    } else {
        // Go up the tree as long as you're the right child
        Node<T>* childNode = node_;
        nextNode = node_->parent;
        while (nextNode != nullptr && nextNode->right == childNode) {
            childNode = nextNode;
            nextNode = nextNode->parent;
        }
    }

    T result = node_->data;
    node_ = nextNode;
    return result;
}
