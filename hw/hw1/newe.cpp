#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
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

struct Facelet{
    unsigned int color0 : BITS_PER_COLOR;
    unsigned int color1 : BITS_PER_COLOR;
    unsigned int color2 : BITS_PER_COLOR;
    unsigned int color3 : BITS_PER_COLOR;
    unsigned int color4 : BITS_PER_COLOR;
    unsigned int color5 : BITS_PER_COLOR;
    unsigned int color6 : BITS_PER_COLOR;
    unsigned int color7 : BITS_PER_COLOR;
    unsigned int color8 : BITS_PER_COLOR;
    unsigned int color9 : BITS_PER_COLOR;
    unsigned int color10 : BITS_PER_COLOR;
    unsigned int color11 : BITS_PER_COLOR;
    unsigned int color12 : BITS_PER_COLOR;
    unsigned int color13 : BITS_PER_COLOR;
    unsigned int color14 : BITS_PER_COLOR;
    unsigned int color15 : BITS_PER_COLOR;
    unsigned int color16 : BITS_PER_COLOR;
    unsigned int color17 : BITS_PER_COLOR;
    unsigned int color18 : BITS_PER_COLOR;
    unsigned int color19 : BITS_PER_COLOR;
    unsigned int color20 : BITS_PER_COLOR;
    unsigned int color21 : BITS_PER_COLOR;
    unsigned int color22 : BITS_PER_COLOR;
    unsigned int color23 : BITS_PER_COLOR;
};

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
    Facelet Cube;
};

void PocketCube::SetFacelet(int index, __uint128_t color) {
    switch(index){
        case 0: Cube.color0 = color; break;
        case 1: Cube.color1 = color; break;
        case 2: Cube.color2 = color; break;
        case 3: Cube.color3 = color; break;
        case 4: Cube.color4 = color; break;
        case 5: Cube.color5 = color; break;
        case 6: Cube.color6 = color; break;
        case 7: Cube.color7 = color; break;
        case 8: Cube.color8 = color; break;
        case 9: Cube.color9 = color; break;
        case 10: Cube.color10 = color; break;
        case 11: Cube.color11 = color; break;
        case 12: Cube.color12 = color; break;
        case 13: Cube.color13 = color; break;
        case 14: Cube.color14 = color; break;
        case 15: Cube.color15 = color; break;
        case 16: Cube.color16 = color; break;
        case 17: Cube.color17 = color; break;
        case 18: Cube.color18 = color; break;
        case 19: Cube.color19 = color; break;
        case 20: Cube.color20 = color; break;
        case 21: Cube.color21 = color; break;
        case 22: Cube.color22 = color; break;
        case 23: Cube.color23 = color; break;
    }
}

int PocketCube::GetFacelet(int index) const {
    switch(index){
        case 0: return Cube.color0;
        case 1: return Cube.color1;
        case 2: return Cube.color2;
        case 3: return Cube.color3;
        case 4: return Cube.color4;
        case 5: return Cube.color5;
        case 6: return Cube.color6;
        case 7: return Cube.color7;
        case 8: return Cube.color8;
        case 9: return Cube.color9;
        case 10: return Cube.color10;
        case 11: return Cube.color11;
        case 12: return Cube.color12;
        case 13: return Cube.color13;
        case 14: return Cube.color14;
        case 15: return Cube.color15;
        case 16: return Cube.color16;
        case 17: return Cube.color17;
        case 18: return Cube.color18;
        case 19: return Cube.color19;
        case 20: return Cube.color20;
        case 21: return Cube.color21;
        case 22: return Cube.color22;
        case 23: return Cube.color23;
    }
    return 0;
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
    std::cout << a << std::endl;
    std::cout << sizeof(a) << std::endl;
 }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }
void Test8() { /* HIDDEN */ }
void Test9() { /* HIDDEN */ }