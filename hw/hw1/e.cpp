#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx,avx2,fma,sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")

#include <iostream>
class PocketCube 
{
    friend std::ostream& operator<<(std::ostream&, const PocketCube&);
public:
    PocketCube();
    PocketCube RotateFront();
    PocketCube RotateRight();
    PocketCube RotateDown();
private:
    char cube[6][8] = {
        {'-', '-', 'W', 'W', '-', '-', '-', '-'},
        {'-', '-', 'W', 'W', '-', '-', '-', '-'},
        {'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B'},
        {'O', 'O', 'G', 'G', 'R', 'R', 'B', 'B'},
        {'-', '-', 'Y', 'Y', '-', '-', '-', '-'},
        {'-', '-', 'Y', 'Y', '-', '-', '-', '-'}
    };
    char cpy[6][8];
};

std::ostream& operator<<(std::ostream& os, const PocketCube& pc) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            os << pc.cube[i][j];
        }
        os << std::endl;
    }
    return os;
}

PocketCube::PocketCube() {
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 8; j++){
            cpy[i][j] = cube[i][j];
        }
    }
}

PocketCube PocketCube::RotateFront()  {
    cube[1][2] = cpy[3][1]; cube[1][3] = cpy[2][1];
    cube[3][1] = cpy[4][3]; cube[2][1] = cpy[4][2]; 
    cube[4][3] = cpy[2][4]; cube[4][2] = cpy[3][4];
    cube[2][4] = cpy[1][2]; cube[3][4] = cpy[1][3];

    cpy[2][2] = cube[2][2]; cpy[3][2] = cube[3][2];
    cpy[2][3] = cube[2][3]; cpy[3][3] = cube[3][3];

    cube[2][2] = cpy[3][2]; cube[2][3] = cpy[2][2];
    cube[3][2] = cpy[3][3]; cube[3][3] = cpy[2][3];

    // copy

    cpy[1][2] = cube[1][2]; cpy[1][3] = cube[1][3];
    cpy[3][1] = cube[3][1]; cpy[2][1] = cube[2][1];
    cpy[4][3] = cube[4][3]; cpy[4][2] = cube[4][2];
    cpy[2][4] = cube[2][4]; cpy[3][4] = cube[3][4];

    cpy[2][2] = cube[2][2]; cpy[3][2] = cube[3][2];
    cpy[2][3] = cube[2][3]; cpy[3][3] = cube[3][3];

    return *this;
}

PocketCube PocketCube::RotateRight()  {
    cube[0][3] = cpy[2][3]; cube[1][3] = cpy[3][3];
    cube[2][3] = cpy[4][3]; cube[3][3] = cpy[5][3];
    cube[4][3] = cpy[3][6]; cube[5][3] = cpy[2][6];
    cube[2][6] = cpy[1][3]; cube[3][6] = cpy[0][3];
    
    cpy[2][4] = cube[2][4]; cpy[3][4] = cube[3][4];
    cpy[2][5] = cube[2][5]; cpy[3][5] = cube[3][5];
    
    cube[2][4] = cpy[3][4]; cube[2][5] = cpy[2][4];
    cube[3][4] = cpy[3][5]; cube[3][5] = cpy[2][5];

    // copy

    cpy[0][3] = cube[0][3]; cpy[1][3] = cube[1][3];
    cpy[2][3] = cube[2][3]; cpy[3][3] = cube[3][3];
    cpy[4][3] = cube[4][3]; cpy[5][3] = cube[5][3];
    cpy[2][6] = cube[2][6]; cpy[3][6] = cube[3][6];

    cpy[2][4] = cube[2][4]; cpy[3][4] = cube[3][4];
    cpy[2][5] = cube[2][5]; cpy[3][5] = cube[3][5];

    return *this;
}

PocketCube PocketCube::RotateDown()  {
    for(int i = 0; i < 8; i++){
        cube[3][i] = cpy[3][(i - 2 + 8) % 8];
    }

    cpy[4][2] = cube[4][2]; cpy[4][3] = cube[4][3];
    cpy[5][2] = cube[5][2]; cpy[5][3] = cube[5][3];

    cube[4][2] = cpy[5][2]; cube[4][3] = cpy[4][2];
    cube[5][2] = cpy[5][3]; cube[5][3] = cpy[4][3];

    // copy

    for(int i = 0; i < 8; i++){
        cpy[3][i] = cube[3][i];
    }

    cpy[4][2] = cube[4][2]; cpy[4][3] = cube[4][3];
    cpy[5][2] = cube[5][2]; cpy[5][3] = cube[5][3];

    return *this;
}