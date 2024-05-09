#include <vector>
#include <memory>
#include <iostream>
#include <random>     // For Test
#include <set>        // For Test
#include <unordered_set> // For Test
#include <cassert>    // For Test
#include <functional> // For Test

using StoreId = unsigned int;
using BookId = unsigned int;

struct Stock {
    BookId bookId;
    StoreId storeId;
    unsigned int price;    
};

class IBookStores {
public:
    virtual void Initialize(const std::vector<Stock>& stocks) = 0;
    virtual std::vector<Stock> SearchUnrentedStocksOrderdByPrice(BookId bookId, std::size_t maxCount = 10) const = 0;
    virtual void Rent(BookId bookId, StoreId storeId) = 0;
    virtual void Return(BookId bookId, StoreId storeId) = 0;
    virtual std::vector<Stock> ListRentedStocksOrderedByPrice(std::size_t maxCount = 10) const = 0;
    virtual ~IBookStores() {}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s) {
    if (s.empty()) {
        return os << "[]";
    }
    os << '[' << s[0];
    for (std::size_t i = 1; i < s.size(); ++i) {
        os << ", " << s[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Stock& s) {
    return os << "{Book: " << s.bookId << ", Store: " << s.storeId << ", Price: " << s.price << "}";
}

std::unique_ptr<IBookStores> CreateBookStores();

void Test1(); // Sample1
void Test2(); // Rent, Return, ListRentedStocksOrderedByPrice
void Test3(); // Rent, Return, SearchUnrentedStocksOrderdByPrice
void Test4(); // All
void Test5(); // Rent, Return, ListRentedStocksOrderedByPrice
void Test6(); // Rent, Return, SearchUnrentedStocksOrderdByPrice
void Test7(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id-1]();
}

std::string format(std::size_t idx) {
    if (idx < 10) return "0" + std::to_string(idx) + ") ";
    return std::to_string(idx) + ") ";
}

void Test1() {
    std::unique_ptr<IBookStores> bookStores = CreateBookStores();

    std::vector<Stock> stocks{
        {7, 1, 6}, {7, 2, 9}, {7, 16, 71}, {7, 5, 9},
        {0, 1, 10}, {0, 2, 20}, {0, 3, 30}, {0, 4, 0}, {0, 5, 1}, {0, 6, 0}, {0, 7, 1},
        {1, 1, 0},  {1, 2, 20}, {1, 3, 40}
    };

    // 實作 Initialize，初始化書店的庫存，同一本書在同一間書店只會有一筆庫存
    // - 每筆庫存有三個欄位，分別是書本編號 (bookId)、書店編號 (storeId)、租借價格 (price)
    // - 書本編號和書店編號都是從 0 開始的正整數 (unsigned int)
    // - 同一本書在不同書店的租借價格可能不同
    {
        bookStores->Initialize(stocks);
    }

    // 實作 Rent(bookId, storeId)，從指定書店編號 (storeId) 租借一本指定書本編號 (bookId) 的書
    // - 每本提供租借的書在同一個書店只會有一筆庫存，且租借價格不會變動
    // - 當該本書從該書店被借走後，該書店就不會再提供該本書的租借，直到該本書被歸還
    // - 如果指定書店沒有提供指定書本的租借或該本書已經被借走了，則進行租借為《未定義行為》
    // 實作 Return(bookId, storeId)，歸還一本書 (bookdId) 回指定書店 (storeId)
    // - 只能把租借的書歸還回原本租借的書店 
    // - 歸還後，該本書又可以再於原本租借的書店提供租借，且租借價格不會變動
    // - 如果該本書在指定書店沒有被借走或本來就沒有庫存，則進行歸還為《未定義行為》
    // 實作 ListRentedStocksOrderedByPrice(maxCount)，列出所有已租借的書中，依照下面指定順序排列的前面 maxCount 筆資料：
    // - 租借價格 (price) 低的排在前面; 租借價格一樣時，書本編號 (bookId) 小的排在前面; 書本編號也一樣時, 書店編號 (storeId) 小的排在前面
    // - maxCount 代表最多要列出的書本數量，如果 maxCount 大於已租借的書本數量或 maxCount 為 -1 時，則列出全部已租借的書
    // - maxCount 最多為 20
    {
        bookStores->Rent(0, 1);
        std::cout << "01) " << bookStores->ListRentedStocksOrderedByPrice() << std::endl;

        bookStores->Rent(0, 2);
        std::cout << "02) " << bookStores->ListRentedStocksOrderedByPrice() << std::endl;

        bookStores->Rent(1, 1);
        bookStores->Rent(1, 2);
        std::cout << "03) " << bookStores->ListRentedStocksOrderedByPrice() << std::endl;
        std::cout << "04) " << bookStores->ListRentedStocksOrderedByPrice(3) << std::endl;

        bookStores->Return(1, 1);
        bookStores->Return(0, 1);
        std::cout << "05) " << bookStores->ListRentedStocksOrderedByPrice() << std::endl;
    }

    // 實作 SearchUnrentedStocksOrderdByPrice(bookId, maxCount)，列出所有指定書本編號 (bookId) 且尚未被租借走的書中，依照下面指定順序排列的前面 maxCount 筆資料
    // - 租借價格 (price) 低的排在前面; 租借價格一樣時，書本編號 (bookId) 小的排在前面; 書本編號也一樣時, 書店編號 (storeId) 小的排在前面
    // - maxCount 代表最多要列出的書本數量，如果 maxCount 大於尚未被租借的書本數量或 maxCount 為 -1 時，則列出全部尚未被租借的書
    // - maxCount 最多為 20
    {
        std::cout << "06) " << bookStores->SearchUnrentedStocksOrderdByPrice(0) << std::endl;
        std::cout << "07) " << bookStores->SearchUnrentedStocksOrderdByPrice(7, 3) << std::endl;
    }
}


namespace Feis {}
void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }

// [YOUR CODE WILL BE PLACED HERE]
#include <map>

long long makeHash(BookId bookid, StoreId StoreId){
    return (long long)bookid * 1000000 + StoreId;
}

std::pair<BookId, StoreId> splitHash(long long hash){
    return {hash / 1000000, hash % 1000000};
}

bool cmp(const Stock& a, const Stock& b) {
    if (a.price != b.price) return a.price < b.price;
    if (a.bookId != b.bookId) return a.bookId < b.bookId;
    return a.storeId < b.storeId;
}

class BookStores : public IBookStores {
public:
    void Initialize(const std::vector<Stock>& stocks) override {
        stocks_ = stocks;
    }

    std::vector<Stock> SearchUnrentedStocksOrderdByPrice(BookId bookId, std::size_t maxCount = 10) const override {
        std::vector<Stock> res;
        for (const auto& stock : stocks_) {
            if (stock.bookId == bookId) {
                res.push_back(stock);
            }
        }
        std::sort(res.begin(), res.end(), cmp);
        if (maxCount == -1 || maxCount > res.size()) return res;

        return std::vector<Stock>(res.begin(), res.begin() + maxCount);
    }

    void Rent(BookId bookId, StoreId storeId) override {
        for (auto it = stocks_.begin(); it != stocks_.end(); ++it) {
            if (it->bookId == bookId && it->storeId == storeId) {
                rentedStocks_[makeHash(bookId, storeId)] = *it;
                stocks_.erase(it);
                return;
            }
        }
    }

    void Return(BookId bookId, StoreId storeId) override {
        auto it = rentedStocks_.find(makeHash(bookId, storeId));
        if (it != rentedStocks_.end()) {
            stocks_.push_back(it->second);
            rentedStocks_.erase(it);
        }
    }

    std::vector<Stock> ListRentedStocksOrderedByPrice(std::size_t maxCount = 10) const override {
        std::vector<Stock> res;
        for (const auto& [_, stock] : rentedStocks_) {
            res.push_back(stock);
        }
        std::sort(res.begin(), res.end(), cmp);

        if (maxCount == -1 || maxCount > res.size()) return res;
        return std::vector<Stock>(res.begin(), res.begin() + maxCount);
    }

private:
    std::vector<Stock> stocks_;
    std::map< long long, Stock> rentedStocks_;
};

std::unique_ptr<IBookStores> CreateBookStores() {
    return std::make_unique<BookStores>();
}
