#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // For Test
#include <random>    // For Test

struct IStringDatabase {
    virtual void Add(const std::string&) = 0;
    virtual bool Remove(const std::string&) = 0;
    virtual std::vector<std::string> StartsWith(const std::string& prefix) = 0;
    virtual ~IStringDatabase() {}
};

#include <unordered_set>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class StringDatabase : public IStringDatabase {
private:
    TrieNode* root;

public:
    StringDatabase() {
        root = new TrieNode();
    }

    void Add(const std::string& str) override {
        TrieNode* curr = root;
        for (char c : str) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    bool Remove(const std::string& str) override {
        TrieNode* curr = root;
        std::unordered_set<TrieNode*> nodesToDelete;
        for (char c : str) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
            nodesToDelete.insert(curr);
        }
        if (!curr->isEndOfWord) {
            return false;
        }
        curr->isEndOfWord = false;

        // Remove nodes that are not part of any other word
        for (int i = str.size() - 1; i >= 0; --i) {
            curr = root;
            for (int j = 0; j < i; ++j) {
                curr = curr->children[str[j]];
                nodesToDelete.erase(curr);
            }
            curr->children.erase(str[i]);
            if (curr->children.size() > 0) {
                break;
            }
        }

        // Delete the nodes that are not part of any other word
        for (auto node : nodesToDelete) {
            delete node;
        }

        return true;
    }

    std::vector<std::string> StartsWith(const std::string& prefix) override {
        std::vector<std::string> result;
        TrieNode* curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) {
                return result;
            }
            curr = curr->children[c];
        }
        TraverseTrie(curr, prefix, result);
        std::sort(result.begin(), result.end());
        return result;
    }

    void TraverseTrie(TrieNode* node, std::string prefix, std::vector<std::string>& result) {
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        for (auto& child : node->children) {
            TraverseTrie(child.second, prefix + child.first, result);
        }
    }

    ~StringDatabase() {
        DeleteTrie(root);
    }

    void DeleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& child : node->children) {
            DeleteTrie(child.second);
        }
        delete node;
    }
};


void Test1(); // Sample1
void Test2(); // Add, StartsWith
void Test3(); // Add, StartsWith
void Test4(); // Add, StartsWith
void Test5(); // All
void Test6(); // All
void Test7(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id-1]();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << '[';
    if (v.size() > 0) {
        os << v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            os << ", " << v[i];
        }
    }
    return os << ']';
}

namespace Feis {}

void Test1() {
    IStringDatabase&& db = StringDatabase();
    db.Add("Helloworld");
    db.Add("HelloWorld");
    db.Add("Hello");
    db.Add("Helloworld");
    db.Add("Hello");
    db.Add("Hi");

    std::cout << "01) " << db.StartsWith("Hello") << std::endl;
    std::cout << "02) " << db.StartsWith("hello") << std::endl;
    std::cout << "03) " << db.StartsWith("H") << std::endl;

    db.Remove("Helloworld");
    db.Remove("Hi");
    std::cout << "04) " << db.StartsWith("H") << std::endl;
}

void Test2() {
}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}