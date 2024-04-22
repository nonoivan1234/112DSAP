#include <iostream>
#include <random>
#include <functional>
#include <cassert>

// 模板參數 T 的合法型態會支援：
// - 值初始化：歸零
// - 複製語意：複製建構與賦值
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string 等等
template<typename T>
struct Node {
    T data;
    int meta{};
    Node<T>* left{};
    Node<T>* right{};
    explicit Node(const T& data) : data{data} {}
};

template<typename T>
class BalancedBinarySearchTreeSet {
public:
    BalancedBinarySearchTreeSet() = default;
    BalancedBinarySearchTreeSet(const BalancedBinarySearchTreeSet<T>&) = delete;
    ~BalancedBinarySearchTreeSet();
    BalancedBinarySearchTreeSet<T>& operator=(const BalancedBinarySearchTreeSet<T>&) = delete;
    [[nodiscard]] bool Contains(const T &) const;
    bool Add(const T &data);
    bool Remove(const T &);
    [[nodiscard]] std::vector<T> ToVector() const;
    [[nodiscard]] size_t Size() const { return size_; }
    [[nodiscard]] int Height() const;

private:
    Node<T> *root_{};
    size_t size_{};
};

void Test1(); // Sample1
void Test2(); // Add
void Test3(); // Add, ToVector
void Test4(); // Add, Remove, ToVector
void Test5(); // Add, Remove, ToVector

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5 };
    f[id-1]();
}

namespace {
    template<typename T>
    int GetHeight(Node<T>* root) {
        if (!root) return -1;
        return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
    }

    template<typename T>
    bool ValidateHeight(BalancedBinarySearchTreeSet<T>& s) {
        return s.Height() <= (2 * log(s.Size() + 2) + 2);
    }
    template<typename T>
    bool Contains(Node<T>* root, const T& data) {
        if (!root) {
            return false;
        }
        if (data < root->data) {
            return Contains(root->left, data);
        }
        if (root->data < data) {
            return Contains(root->right, data);
        }
        return true;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const BalancedBinarySearchTreeSet<T>& s) {
    std::vector<T> v = s.ToVector();
    os << "{";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << v[i];
    }
    os << "}";
    return os;
}

template<typename T>
bool BalancedBinarySearchTreeSet<T>::Contains(const T& data) const {
    return ::Contains(root_, data);
}

template<typename T>
int BalancedBinarySearchTreeSet<T>::Height() const {
    return GetHeight(root_);
}

namespace Feis { /* HIDDEN */ }

void Test1() {
    std::cout << std::boolalpha;

    // 實作 Add(val) 方法
    // - 如果要新增的值 val 尚未存在集合中，則將 val 加入集合並回傳 true
    // - 如果要新增的值 val 已經存在集合中，則回傳 false 而不發生其他作用
    {
        BalancedBinarySearchTreeSet<int> s;
        std::cout << "01) " << ValidateHeight(s) << std::endl;
        std::cout << "02) " << s.Contains(3) << std::endl;
        std::cout << "03) " << s.Add(3) << std::endl;
        std::cout << "04) " << s.Add(5) << std::endl;
        std::cout << "05) " << s.Contains(3) << std::endl;
        std::cout << "06) " << s.Add(3) << std::endl;
        std::cout << "07) " << s.Size() << std::endl;
        std::cout << "08) " << ValidateHeight(s) << std::endl;
    }

    // 實作 ToVector() 方法，回傳一個由集合內所有元素所構成的陣列
    // - 陣列中的元素值由小到大排序
    {
        BalancedBinarySearchTreeSet<int> s;
        s.Add(3);
        s.Add(9);
        s.Add(7);
        std::cout << "09) " << s << std::endl;
        s.Add(1);
        s.Add(5);
        std::cout << "10) " << s << std::endl;
        std::cout << "11) " << ValidateHeight(s) << std::endl;
    }

    // 實作 Remove(val) 方法，移除值為 val 的元素
    // - 如果要新增的值 val 已經存在集合中，則將 val 從集合移除並回傳 true
    // - 如果要新增的值 val 尚未存在集合中，則回傳 false 而不發生其他作用
    {
        BalancedBinarySearchTreeSet<int> s;
        s.Add(3);
        s.Add(9);
        s.Add(7);
        std::cout << "12) " << s.Remove(1) << std::endl;
        std::cout << "13) " << s.Remove(3) << std::endl;
        std::cout << "14) " << s << std::endl;
        std::cout << "15) " << s.Remove(7) << std::endl;
        std::cout << "16) " << s.Remove(9) << std::endl;
        std::cout << "17) " << s << std::endl;
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }

// [YOUR CODE WILL BE PLACED HERE]
template<typename T>
BalancedBinarySearchTreeSet<T>::~BalancedBinarySearchTreeSet() {
    std::function<void(Node<T>*)> deleteAll = [&](Node<T>* root) {
        if (!root) return;
        deleteAll(root->left);
        deleteAll(root->right);
        delete root;
    };
    deleteAll(root_);
}

template<typename T>
void RotateRight(Node<T>*& root) {
    Node<T>* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
}

template<typename T>
void RotateLeft(Node<T>*& root) {
    Node<T>* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
}

template<typename T>
void Balance(Node<T>*& root) {
    if (!root) return;
    int leftHeight = GetHeight(root->left);
    int rightHeight = GetHeight(root->right);
    if (leftHeight - rightHeight > 1) {
        if (GetHeight(root->left->right) > GetHeight(root->left->left)) {
            RotateLeft(root->left);
        }
        RotateRight(root);
    } else if (rightHeight - leftHeight > 1) {
        if (GetHeight(root->right->left) > GetHeight(root->right->right)) {
            RotateRight(root->right);
        }
        RotateLeft(root);
    }
}

template<typename T>
T& FindMin(Node<T>*& root) {
    if (!root->left) {
        return root->data;
    }
    return FindMin(root->left);
}

template<typename T>
T& FindMax(Node<T>*& root) {
    if (!root->right) {
        return root->data;
    }
    return FindMax(root->right);
}

template<typename T>
bool add(Node<T>*& root, const T& data) {
    if (!root) {
        root = new Node<T>(data);
        return true;
    }
    if (data < root->data) {
        if (add(root->left, data)) {
            ++root->meta;
            Balance(root);
            return true;
        }
    } else if (root->data < data) {
        if (add(root->right, data)) {
            ++root->meta;
            Balance(root);
            return true;
        }
    }
    return false;
}

template<typename T>
bool BalancedBinarySearchTreeSet<T>::Add(const T& data) {
    if (add(root_, data)) {
        ++size_;
        return true;
    }
    return false;
}

template<typename T>
bool remove(Node<T>*& root, const T& data) {
    if (!root) {
        return false;
    }
    if (data < root->data) {
        if (remove(root->left, data)) {
            --root->meta;
            Balance(root);
            return true;
        }
    } else if (root->data < data) {
        if (remove(root->right, data)) {
            --root->meta;
            Balance(root);
            return true;
        }
    } else {
        if (root->left && root->right) {
            if (root->left->meta < root->right->meta) {
                root->data = FindMin(root->right);
                if (remove(root->right, root->data)) {
                    --root->meta;
                    Balance(root);
                    return true;
                }
            } else {
                root->data = FindMax(root->left);
                if (remove(root->left, root->data)) {
                    --root->meta;
                    Balance(root);
                    return true;
                }
            }
        } else {
            Node<T>* old = root;
            root = root->left ? root->left : root->right;
            delete old;
            return true;
        }
    }
    return false;
}

template<typename T>
bool BalancedBinarySearchTreeSet<T>::Remove(const T& data) {
    if (remove(root_, data)) {
        --size_;
        return true;
    }
    return false;
}

template<typename T>
void toVector(Node<T>* root, std::vector<T>& v) {
    if (!root) return;
    toVector(root->left, v);
    v.push_back(root->data);
    toVector(root->right, v);
}

template<typename T>
std::vector<T> BalancedBinarySearchTreeSet<T>::ToVector() const {
    std::vector<T> v;
    v.reserve(size_);
    toVector(root_, v);
    return v;
}