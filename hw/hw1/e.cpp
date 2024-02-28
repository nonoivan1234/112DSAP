#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <iostream>

static const uint8_t arr[6] = {2, 2, 8, 8, 2, 2};
static const uint8_t color[6] = {'W', 'O', 'G', 'R', 'B', 'Y'};

class PocketCube 
{
    friend std::ostream& operator<<(std::ostream&, const PocketCube&);
public:
    PocketCube();
    inline PocketCube RotateFront();
    inline PocketCube RotateRight();
    inline PocketCube RotateDown();
private:
    uint8_t cube[24] = {0, 0, 0, 0, 
        1, 1, 2, 2, 3, 3, 4, 4, 
        1, 1, 2, 2, 3, 3, 4, 4,
        5, 5, 5, 5
    };
};

std::ostream& operator<<(std::ostream& os, const PocketCube& pc) {
    uint8_t idx = 0;
    for(uint8_t i = 0; i < 6; i++){
        if(arr[i] != 8) os << "--";
        for(uint8_t j = 0; j < arr[i]; j++){
            os << color[pc.cube[idx++]];
        }
        if(arr[i] != 8) os << "----";
        os << std::endl;
    }
    return os;
}

PocketCube::PocketCube() {}

inline PocketCube PocketCube::RotateFront()  {
    uint8_t tmp1 = cube[2];

    cube[2] = cube[13]; cube[13] = cube[21];
    cube[21] = cube[8]; cube[8] = tmp1;

    tmp1 = cube[3];

    cube[3] = cube[5]; cube[5] = cube[20];
    cube[20] = cube[16]; cube[16] = tmp1;

    tmp1 = cube[6];

    cube[6] = cube[14]; cube[14] = cube[15];
    cube[15] = cube[7]; cube[7] = tmp1;

    return *this;
}

inline PocketCube PocketCube::RotateRight()  {
    uint8_t tmp1 = cube[1];

    cube[1] = cube[7]; cube[7] = cube[21];
    cube[21] = cube[18]; cube[18] = tmp1;

    tmp1 = cube[3];

    cube[3] = cube[15]; cube[15] = cube[23];
    cube[23] = cube[10]; cube[10] = tmp1;

    tmp1 = cube[8];

    cube[8] = cube[16]; cube[16] = cube[17];
    cube[17] = cube[9]; cube[9] = tmp1;

    return *this;
}

inline PocketCube PocketCube::RotateDown()  {
    uint8_t tmp1 = cube[12];

    cube[12] = cube[18]; cube[18] = cube[16];
    cube[16] = cube[14]; cube[14] = tmp1;

    tmp1 = cube[13];

    cube[13] = cube[19]; cube[19] = cube[17];
    cube[17] = cube[15]; cube[15] = tmp1;

    tmp1 = cube[20];

    cube[20] = cube[22]; cube[22] = cube[23];
    cube[23] = cube[21]; cube[21] = tmp1;

    return *this;
}

#include <iostream>
#include <random>     // For Test
#include <vector>     // For Test

void Test1(); // Sample1
void Test2(); // All 
void Test3(); // RotateRight, RotateDown 
void Test4(); // 重複其中一種旋轉
void Test5(); // 同時有多個
void Test6(); // All
void Test7(); // RotateRight, RotateDown
void Test8(); // 重複其中一種旋轉
void Test9(); // 同時有多個

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9};
    f[id-1]();
}

void Test1() {
    PocketCube a, b, c, d;

    std::cout << a << std::endl;
    std::cout << a.RotateFront() << std::endl;
    std::cout << a << std::endl;

    std::cout << b << std::endl;
    std::cout << b.RotateDown() << std::endl;
    std::cout << b << std::endl;

    std::cout << c << std::endl;
    std::cout << c.RotateRight() << std::endl;
    std::cout << c << std::endl;

    std::cout << d.RotateFront().RotateRight().RotateDown().RotateRight() << std::endl;
    std::cout << PocketCube().RotateFront().RotateFront().RotateFront().RotateFront() << std::endl;
}

void Test2() { 
    PocketCube a;
    std::cout << a.RotateDown().RotateFront().RotateRight() << std::endl;
 }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }
void Test8() { /* HIDDEN */ }
void Test9() { /* HIDDEN */ }