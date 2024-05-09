#include <vector>
#include <iostream>
#include <iomanip>
#include <random>    // For Testing
#include <algorithm> // For Testing
struct TreeNode {
    int value;
    int left = -1;  // left index
    int right = -1; // right index
};

std::ostream& operator<<(std::ostream& os, const TreeNode& node) {
    return os << '{' << node.value << ", " << node.left << ", " << node.right << '}';
}

std::ostream& operator<<(std::ostream& os, const std::vector<TreeNode>& nodes) {
    if (nodes.size() == 0) {
        return os << "[]";
    }
    os << '[' << nodes[0];
    for (std::size_t i = 1; i < nodes.size(); ++i) {
        os << ", " << nodes[i];
    }
    return os << ']';
}

bool Check(const std::vector<TreeNode>& nodes, int root);

void Test1(); // Sample
void Test2(); // root >= 0
void Test3(); // root == -1
void Test4(); // All
void Test5(); // root == -1
void Test6(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6};
    f[id-1]();
}

void Test1() {
    /***
     * a:       (6)
     *         /   \
     *      (-1)   (13)
     *        \     /\
     *        (2) (9)(17)
     ***/
    std::vector<TreeNode> a = {{9, -1, -1}, {17, -1, -1}, {-1, -1, 4}, {13, 0, 1}, {2, -1, -1}, {6, 2, 3}};
    /***
     * b:      (1)
     *         / \
     *       (2) (3)
     ***/            
    std::vector<TreeNode> b = {{1, 1, 2}, {2, -1, -1}, {3, -1, -1}};
    std::vector<TreeNode> c = {{2, 1, 2}, {1, -1, -1}, {3, -1, -1}, {4, -1, -1}};
    std::cout << "01) " << std::boolalpha << Check(a, -1) << std::endl;
    std::cout << "02) " << std::boolalpha << Check(a, -0)  << std::endl;
    std::cout << "03) " << std::boolalpha << Check(b, -1) << std::endl;
    std::cout << "04) " << std::boolalpha << Check(c, -1) << std::endl;    
}

namespace Feis { /* HIDDEN */ }

void Test2() {
    std::vector<TreeNode> a = {{9, -1, -1}, {17, -1, -1}, {-1, -1, 4}, {13, 0, 1}, {2, -1, -1}, {6, 2, 3}};

    std::cout << "01) " << std::boolalpha << Check(a, 5) << std::endl;
}
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() {  Test3(); }
void Test6() {  Test4(); }

// [YOUR CODE WILL BE PLACED HERE] 

#include <climits>

bool dfs(const std::vector<TreeNode>& nodes, int now, std::vector<bool>& visited, int mn, int mx){
    if (now == -1) {
        return true;
    }
    int n = nodes.size();
    int left = nodes[now].left;
    int right = nodes[now].right;

    if (nodes[now].value <= mn || nodes[now].value >= mx) {
        return false;
    }

    visited[now] = true;

    if (!dfs(nodes, left, visited, mn, nodes[now].value)) {
        return false;
    }

    if (!dfs(nodes, right, visited, nodes[now].value, mx)) {
        return false;
    }

    return true;
}

#include <stack>
bool Check(const std::vector<TreeNode>& nodes, int root) {
    if (root < 0) {
        std::vector<bool> findRoot(nodes.size(), false);
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].left != -1) {
                findRoot[nodes[i].left] = true;
            }
            if (nodes[i].right != -1) {
                findRoot[nodes[i].right] = true;
            }
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (findRoot[i])    continue;

            if (Check(nodes, i)) {
                return true;
            }
        }
        return false;
    }

    std::vector<bool> visited(nodes.size(), false);
    if (dfs(nodes, root, visited, INT_MIN, INT_MAX)){
        for(int i = 0; i < nodes.size(); i++){
            if (!visited[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}