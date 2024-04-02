#include <string>
#include <iostream>
#include <vector>     // For Test
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

// Case Insensitive String
class CIString {
    // TODO: case insensitive string comparision
    friend bool operator<(const CIString& lhs, const CIString& rhs);
    friend bool operator>(const CIString& lhs, const CIString& rhs);
    friend bool operator==(const CIString& lhs, const CIString& rhs);
    friend bool operator!=(const CIString& lhs, const CIString& rhs);

    // TODO: concatenate strings
    friend CIString operator+(const CIString& lhs, const CIString& rhs);

public:
    // copy
    CIString(const CIString& other) = default;

    // move
    CIString(CIString&& other) = default;

    // construct from C String
    CIString(const char* other) : repr_{other} {}

    // construct from C++ String (copy)
    CIString(const std::string& other) : repr_{other} {}

    // construct from C++ String (move)
    CIString(std::string&& other) : repr_{std::move(other)} {}

    // access the specified character
    char& operator[](size_t pos);
    char operator[](size_t pos) const;

    // clears the contents
    void Clear();

    // returns the number of characters
    size_t Length() const;

    // TODO: appends string to the end
    CIString& Append(const CIString& other);
    CIString& operator+=(const CIString& string);

    // TODO: appends character to the end
    CIString& Append(char ch);
    CIString& operator+=(char ch);

    // TODO: find string in the string
    size_t Find(const CIString& s, size_t start = 0) const;

    // TODO: find character in the string
    size_t Find(char ch, size_t start = 0) const;

    // TODO: returns a substring
    CIString Substr(size_t pos, size_t len) const;

    // TODO: swaps the contents
    void Swap(CIString& other);

private:
    std::string repr_;
};

std::ostream& operator<<(std::ostream& os, const CIString& s);

void Test1(); // Sample1
void Test2(); // operator==, operator!=
void Test3(); // operator<, operator>, operator+
void Test4(); // Append(char), operator+=(char), Append(const CIString&), operator+=(const CIString&)
void Test5(); // Find(const CIString&, size_t), Find(char, size_t)
void Test6(); // Substr(pos, len), Swap(other)
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
    // Part 1. operator==, operator!=
    {
        const CIString a = "Hello!";
        const CIString b = "HELLO!";
        const CIString c = "Hello world";

        std::cout << "1.1) " << std::boolalpha << (a == b) << std::endl;
        std::cout << "1.2) " << std::boolalpha << (a != b) << std::endl;
        std::cout << "1.3) " << std::boolalpha << (a == c) << std::endl;
        std::cout << "1.4) " << std::boolalpha << (a != c) << std::endl;
    }

    // Part 2. operator<, operator>, operator+
    {
        const CIString a = "Hello!";
        const CIString b = "HELLO!";
        const CIString c = "Hello world";
        const CIString d = "world";
        const CIString e = "Hello#";
        std::cout << "2.1) " << std::boolalpha << (a > b) << std::endl;
        std::cout << "2.2) " << std::boolalpha << (a < b) << std::endl;
        std::cout << "2.3) " << std::boolalpha << (a > c) << std::endl;
        std::cout << "2.4) " << std::boolalpha << (a < c) << std::endl;
        std::cout << "2.5) " << std::boolalpha << (a > d) << std::endl;
        std::cout << "2.6) " << std::boolalpha << (a < d) << std::endl;

        std::cout << "2.7) " << (a + b) << std::endl;
        std::cout << "2.8) " << (a + " " + d) << std::endl;
    }

    // Part 3. Append(char), operator+=(char), Append(const CIString&), operator+=(const CIString&)
    {   
        CIString a = "Hello!";

        std::cout << "3.1) " << a.Append('!').Append('!') << std::endl;
        std::cout << "3.2) " << a << std::endl;

        CIString b = "World";
        std::cout << "3.3) " << a.Append(b) << std::endl;
        std::cout << "3.4) " << a << std::endl;
        std::cout << "3.5) " << b << std::endl;

        CIString c = "Compile";
        std::cout << "3.6) " << (c += ' ') << std::endl;
        std::cout << "3.7) " << (c += "Error") << std::endl;
    }

    // Part 4. Find(const CIString&, size_t), Find(char, size_t)
    {
        const CIString a = "Hello world!";
        std::cout << "4.1) " << a.Find('o') << std::endl;
        std::cout << "4.2) " << a.Find('o', 6) << std::endl;
        std::cout << "4.3) " << a.Find("") << std::endl;
        std::cout << "4.4) " << a.Find("WOr") << std::endl;
        std::cout << "4.5) " << a.Find("WOrld!") << std::endl;
        std::cout << "4.6) " << a.Find("WOr", 7) << std::endl;
    }

    // Part 5. Substr(pos, len), Swap(other)
    {
        CIString a = "Hello world!";
        std::cout << "5.1) " << a.Substr(2, 3) << std::endl;
        std::cout << "5.2) " << a.Substr(1, 0) << std::endl;
        std::cout << "5.3) " << a << std::endl;

        CIString b = "Runtime Error";
        a.Swap(b);
        std::cout << "5.4) " << a << std::endl;
        std::cout << "5.5) " << b << std::endl;
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }

std::ostream& operator<<(std::ostream& os, const CIString& s) {
    for (size_t i = 0; i < s.Length(); ++i) {
        os << s[i];
    }
    return os;
}


char CIString::operator[](size_t pos) const {
    return repr_[pos];
}

char& CIString::operator[](size_t pos) {
    return repr_[pos];
}

size_t CIString::Length() const {
    return repr_.length();
}

void CIString::Clear() {
    repr_.clear();
}

// [YOUR CODE WILL BE PLACED HERE]

void CIString::Swap(CIString& other) {
    repr_.swap(other.repr_);
}

CIString& CIString::Append(const CIString& other) {
    repr_ += other.repr_;
    return *this;
}

CIString& CIString::operator+=(const CIString& string) {
    return Append(string);
}

CIString& CIString::Append(char ch) {
    repr_ += ch;
    return *this;
}

CIString& CIString::operator+=(char ch) {
    return Append(ch);
}

size_t CIString::Find(const CIString& s, size_t start) const {
    if(s.Length() == 0) return 0;
    
    for (size_t i = start; i < repr_.length(); ++i) {
        if (i + s.Length() > repr_.length()) return repr_.length();
        bool found = true;
        for (size_t j = 0; j < s.Length(); ++j) {
            if (tolower(repr_[i + j]) != tolower(s[j])) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return repr_.length();
}

size_t CIString::Find(char ch, size_t start) const {
    for (size_t i = start; i < repr_.length(); ++i) {
        if (tolower(repr_[i]) == tolower(ch)) return i;
    }
    return repr_.length();
}

CIString CIString::Substr(size_t pos, size_t len) const {
    return CIString(repr_.substr(pos, len));
}

bool operator<(const CIString& lhs, const CIString& rhs) {
    for(size_t i = 0; i < lhs.Length() && i < rhs.Length(); ++i) {
        if(tolower(lhs[i]) < tolower(rhs[i])) return true;
        if(tolower(lhs[i]) > tolower(rhs[i])) return false;
    }
    return lhs.Length() < rhs.Length();
}

bool operator>(const CIString& lhs, const CIString& rhs) {
    return rhs < lhs;
}

bool operator==(const CIString& lhs, const CIString& rhs) {
    if(lhs.Length() != rhs.Length()) return false;
    for(size_t i = 0; i < lhs.Length(); ++i) {
        if(tolower(lhs[i]) != tolower(rhs[i])) return false;
    }
    return true;
}

bool operator!=(const CIString& lhs, const CIString& rhs) {
    return !(lhs == rhs);
}

CIString operator+(const CIString& lhs, const CIString& rhs) {
    return CIString(lhs.repr_ + rhs.repr_);
}