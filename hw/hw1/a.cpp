#include <iostream>
#include <random>

class Fraction {
    friend std::ostream& operator<<(std::ostream& os, const Fraction& p);
public:
    Fraction();
    Fraction(int nominator, int denominator);
    Fraction operator+(const Fraction& rhs) const;
    Fraction operator-(const Fraction& rhs) const;
    Fraction operator*(const Fraction& rhs) const;
    Fraction operator/(const Fraction& rhs) const;
    bool operator==(const Fraction& rhs) const;
    bool operator!=(const Fraction& rhs) const;
    bool operator<(const Fraction& rhs) const;
    bool operator>(const Fraction& rhs) const;
    bool operator<=(const Fraction& rhs) const;
    bool operator>=(const Fraction& rhs) const;
    bool IsNegative() const;
    operator bool() const;
private:
    int nominator_;
    int denominator_;
};

std::ostream& operator<<(std::ostream& os, const Fraction& p);

void Test1(); // sample
void Test2(); // constructors
void Test3(); // constructors, +, -, *, /
void Test4(); // constructors, +, -, *, /, IsNegative
void Test5(); // constructors, +, -. *, /, casting
void Test6(); // constructors, comparisons

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6 };
    f[id-1]();
}

void Test1() {
    // Fraction 型態物件預設初始化 (default initialization) 後為 "0/1"
    {
        const Fraction p;
        std::cout << p << std::endl;          // 印出 "0/1"
        std::cout << Fraction() << std::endl; // 印出 "0/1"
    }

    // Fraction 型態物件可用兩個 int 值初始化：一個代表分子 (nominator)，另一個代表分母 (denominator)
    // - 分子與分母各自的範圍皆需在 (-10000, 10000) 之間，超過則是《未定義行為》(undefined behavior)
    // 使用operator<< 印出 Fraction 物件時，輸出格式為 "-#/#"
    // - 輸出時是輸出分子分母『約分』後的結果。例如當分子為 4，分母為 2 時，應該印出 "2/1" 而不是 "4/2"
    // 當分母為 0 的情況發生時，稱為 NaN (Not a Number)
    // - NaN 發生的時候，operator<< 要印出 NaN
    {
        const Fraction p(4, 2);
        std::cout << p << std::endl;                                  // 印出 "2/1"

        std::cout << Fraction(-6, 5) << std::endl; // 印出 "-6/5"
        std::cout << Fraction(0, 5) << std::endl;  // 印出 "0/1"
        std::cout << Fraction(7, 0) << std::endl; // 印出 "NaN"
        std::cout << Fraction(0, 0) << std::endl; // 印出 "NaN"
    }

    // Fraction 型態物件可以相加 (+) 、相減 (-)、相乘 (*) 或相除 (/)
    // - 運算元與運算結果在約分後分子分母各自的整數範圍都會在 (-10000, 10000) 之間，超過則是《未定義行為》(undefined behavior)
    // - 當任一個運算元為 NaN 時，其運算結果也為 NaN
    {
        const Fraction p(1, 2), q(6, 8);
        std::cout << (p + q) << std::endl; // 印出 "5/4"
        std::cout << (p - q) << std::endl; // 印出 "-1/4"
        std::cout << (p * q) << std::endl; // 印出 "3/8"
        std::cout << (p / q) << std::endl; // 印出 "2/3"
        std::cout << (Fraction(1, 0) + q) << std::endl; // 印出 "NaN"
    }

    // Fraction 型態物件提供 IsNegative 方法，回傳是否為負數
    // - "-0/1" 會被視為 "0/1"，為正數
    // - NaN 時，會被視為正數
    {
        const Fraction p(-0, 1), q(2, 3);
        std::cout << std::boolalpha;
        std::cout << p.IsNegative() << std::endl; // 印出 "false"
        std::cout << q.IsNegative() << std::endl; // 印出 "false"
        std::cout << (p - q).IsNegative() << std::endl; // 印出 "true"
        std::cout << (p + q).IsNegative() << std::endl; // 印出 "false"
        std::cout << Fraction(1, 0).IsNegative() << std::endl; // 印出 "false"
    }

    // Fraction 型態物件可以隱性轉型成 bool 型態，當不是 NaN 時回傳 true，反之回傳 false
    {
        if (!Fraction(1, 0)) {
            std::cout << "Is NaN" << std::endl;     // 印出 "Is NaN";
        }
        if (Fraction(0, 1)) {
            std::cout << "Is not NaN" << std::endl; // 印出 "Is not NaN"
        }
    }

    // Fraction 型態物件間可以進行比較運算 (==, !=, <, >, <=, >=)
    // - 當任一個運算元為 NaN 時，其運算結果為 false
    {
        const Fraction p(3, 9), q(2, 3);
        std::cout << std::boolalpha;
        std::cout << (p == q) << std::endl; // 印出 "false"
        std::cout << (p != q) << std::endl; // 印出 "true"
        std::cout << (p < q) << std::endl;  // 印出 "true"
        std::cout << (p > q) << std::endl;  // 印出 "false"
        std::cout << (p <= q) << std::endl; // 印出 "true"
        std::cout << (p >= q) << std::endl; // 印出 "false"
        std::cout << (Fraction(1, 0) > q); // 印出 "false"
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() {
    std::cout << Fraction(-1, 2).IsNegative() << std::endl;
    std::cout << (bool)Fraction(1, 0) << std::endl;
}
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }

// [YOUR CODE WILL BE PLACED HERE]
std::ostream& operator<<(std::ostream& os, const Fraction& p){
    if(p)   return os << p.nominator_ << "/" << p.denominator_;
    else    return os << "NaN";
}

Fraction::Fraction(){
    nominator_ = 0;   denominator_ = 1;
}

Fraction::Fraction(int nominator, int denominator){
    nominator_ = nominator;   denominator_ = denominator;
    if(denominator == 0){
        nominator = 1;
        return;
    }

    if(denominator_ < 0){
        denominator_ *= -1;
        nominator_ *= -1;
    }

    int gcd = std::gcd(abs(nominator_), denominator_);

    nominator_ /= gcd;
    denominator_ /= gcd;
}

Fraction Fraction::operator+(const Fraction &rhs) const{
    if(rhs.denominator_ == 0 || this->denominator_ == 0){
        return Fraction(1, 0);
    }

    int den = denominator_ * rhs.denominator_;
    int nom = nominator_ * rhs.denominator_ + rhs.nominator_ * denominator_;

    int gcd = std::gcd(abs(nom), den);

    return Fraction(nom / gcd, den / gcd);
}

Fraction Fraction::operator-(const Fraction &rhs) const{
    if(rhs.denominator_ == 0 || this->denominator_ == 0){
        return Fraction(1, 0);
    }

    int den = denominator_ * rhs.denominator_;
    int nom = nominator_ * rhs.denominator_ - rhs.nominator_ * denominator_;

    int gcd = std::gcd(abs(nom), den);

    return Fraction(nom / gcd, den / gcd);
}

Fraction Fraction::operator*(const Fraction &rhs) const{
    if(rhs.denominator_ == 0 || this->denominator_ == 0){
        return Fraction(1, 0);
    }

    int den = denominator_ * rhs.denominator_;
    int nom = nominator_ * rhs.nominator_;

    int gcd = std::gcd(abs(den), nom);

    return Fraction(nom / gcd, den / gcd);
}

Fraction Fraction::operator/(const Fraction &rhs) const{
    if(rhs.denominator_ == 0 || this->denominator_ == 0){
        return Fraction(1, 0);
    }

    int den = denominator_ * rhs.nominator_;
    int nom = nominator_ * rhs.denominator_;

    int gcd = std::gcd(abs(den), nom);

    return Fraction(nom / gcd, den / gcd);
}

bool Fraction::operator==(const Fraction &rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    return denominator_ == rhs.denominator_ && nominator_ == rhs.nominator_;
}

bool Fraction::operator!=(const Fraction &rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    return denominator_ != rhs.denominator_ || nominator_ != rhs.nominator_;
}

bool Fraction::operator<(const Fraction& rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    Fraction diff = Fraction(this->nominator_, this->denominator_);
    diff = diff - rhs;

    return diff.nominator_ < 0;
}

bool Fraction::operator>(const Fraction& rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    Fraction diff = Fraction(this->nominator_, this->denominator_);
    diff = diff - rhs;

    return diff.nominator_ > 0;
}


bool Fraction::operator<=(const Fraction& rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    Fraction diff = Fraction(this->nominator_, this->denominator_);
    diff = diff - rhs;

    return diff.nominator_ <= 0;
}


bool Fraction::operator>=(const Fraction& rhs) const{
    if(this->denominator_ == 0 || rhs.denominator_ == 0)   return 0;
    Fraction diff = Fraction(this->nominator_, this->denominator_);
    diff = diff - rhs;

    return diff.nominator_ >= 0;
}

bool Fraction::IsNegative() const{
    return (this->nominator_ < 0 && this->denominator_ != 0);
}

Fraction::operator bool() const{
    return this->denominator_ != 0;
}