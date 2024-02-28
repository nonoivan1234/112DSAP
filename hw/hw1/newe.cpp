#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("-ffast-math")
#pragma GCC optimize ("no-stack-protector")
#pragma GCC optimize ("inline")
#pragma GCC optimize ("omit-frame-pointer")
#pragma GCC optimize ("unsafe-math-optimizations")
#pragma GCC optimize ("unsafe-loop-optimizations")
#pragma GCC target("avx,avx2,fma,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#include <iostream>
#include <algorithm>
static const int NUM_FACELETS = 24; 
static const int NUM_COLORS = 6;
static const int BITS_PER_COLOR = 3;    // 6 colors

static const int arr[6] = {2, 2, 8, 8, 2, 2};
static const char color[6] = {'W', 'O', 'G', 'R', 'B', 'Y'};
static const int orig[24] = {0, 0, 0, 0, 
    1, 1, 2, 2, 3, 3, 4, 4, 
    1, 1, 2, 2, 3, 3, 4, 4,
    5, 5, 5, 5
};
static const __uint128_t MASK = (1 << BITS_PER_COLOR) - 1;
__uint128_t shiftedMasks[NUM_FACELETS];

class PocketCube 
{
    friend std::ostream& operator<<(std::ostream&, const PocketCube&);
public:
    PocketCube();
    PocketCube RotateFront();
    PocketCube RotateRight();
    PocketCube RotateDown();
    void SetFacelet(int index, __uint128_t color);
    int GetFacelet(int index) const;
private:
    __uint128_t Cube = 0;

};

void PocketCube::SetFacelet(int index, __uint128_t color) {
    Cube &= ~(shiftedMasks[index]);
    Cube |= (color << (index * BITS_PER_COLOR));
}

int PocketCube::GetFacelet(int index) const {
    int shiftedValue = Cube >> (index * BITS_PER_COLOR);
    int maskedValue = shiftedValue & MASK;
    return maskedValue;
}


std::ostream& operator<<(std::ostream& os, const PocketCube& pc) {
    int idx = 0;
    for(int i = 0; i < 6; i++){
        if(arr[i] != 8) os << "--";
        for(int j = 0; j < arr[i]; j++){
            os << color[pc.GetFacelet(idx++)];
        }
        if(arr[i] != 8) os << "----";
        os << std::endl;
    }
    return os;
}

PocketCube::PocketCube() {
    for(int i = 0; i < NUM_FACELETS; i++){
        SetFacelet(i, orig[i]);
    }

    if(shiftedMasks[0] == 0){
        for(int i = 0; i < NUM_FACELETS; i++){
            shiftedMasks[i] = (MASK << (i * BITS_PER_COLOR));
        }
    }
}


PocketCube PocketCube::RotateFront()  {
    int tmp1 = GetFacelet(2);

    SetFacelet(2, GetFacelet(13));  SetFacelet(13, GetFacelet(21));
    SetFacelet(21, GetFacelet(8));  SetFacelet(8, tmp1);

    tmp1 = GetFacelet(3);

    SetFacelet(3, GetFacelet(5));  SetFacelet(5, GetFacelet(20));
    SetFacelet(20, GetFacelet(16));  SetFacelet(16, tmp1);

    tmp1 = GetFacelet(6);

    SetFacelet(6, GetFacelet(14));  SetFacelet(14, GetFacelet(15));
    SetFacelet(15, GetFacelet(7));  SetFacelet(7, tmp1);

    return *this;
}

PocketCube PocketCube::RotateRight()  {
    int tmp1 = GetFacelet(1);

    SetFacelet(1, GetFacelet(7));  SetFacelet(7, GetFacelet(21));
    SetFacelet(21, GetFacelet(18));  SetFacelet(18, tmp1);
    
    tmp1 = GetFacelet(3);

    SetFacelet(3, GetFacelet(15));  SetFacelet(15, GetFacelet(23));
    SetFacelet(23, GetFacelet(10));  SetFacelet(10, tmp1);

    tmp1 = GetFacelet(8);

    SetFacelet(8, GetFacelet(16));  SetFacelet(16, GetFacelet(17));
    SetFacelet(17, GetFacelet(9));  SetFacelet(9, tmp1);

    return *this;
}

PocketCube PocketCube::RotateDown()  {
    int tmp1 = GetFacelet(12);

    SetFacelet(12, GetFacelet(18));  SetFacelet(18, GetFacelet(16));
    SetFacelet(16, GetFacelet(14));  SetFacelet(14, tmp1);

    tmp1 = GetFacelet(13);

    SetFacelet(13, GetFacelet(19));  SetFacelet(19, GetFacelet(17));
    SetFacelet(17, GetFacelet(15));  SetFacelet(15, tmp1);

    tmp1 = GetFacelet(20);

    SetFacelet(20, GetFacelet(22));  SetFacelet(22, GetFacelet(23));
    SetFacelet(23, GetFacelet(21));  SetFacelet(21, tmp1);

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
 }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }
void Test8() { /* HIDDEN */ }
void Test9() { /* HIDDEN */ }