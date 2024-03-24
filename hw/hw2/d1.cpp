#include<bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
#define nono_is_handsome cin.tie(0); ios_base::sync_with_stdio(0);
#define int long long
const int Field = 40;
const int Row = 1005;
const int Error = 1e9;
const int Max = 10000000;
typedef struct Data{
    char type = -1;   // 0: string, 1: int, 2: equation, 3: bool
    int data;
    int field;
    int row;
    string str;
}Data;

class CSVreader{
public:
    CSVreader(){
        field = 0;
        row = 0;
        memset(vis, 0, sizeof(vis));
    }
    void ReadLine(string line);
    void ParseData();
    void PrintData();
    void Parse(int row, int field, string str);
    int GetVal(Data &d);
private:
    Data data[Row][Field];
    bool vis[Row][Field];
    int field;
    int row;
};

void CSVreader::Parse(int row, int field, string str){
    Data tmp;
    if(str[0] == '#'){
        tmp.type = 0;
        tmp.str = str.substr(1);
        tmp.data = Error;
    }
    else if(str[0] == '='){
        tmp.type = 2;
        tmp.str = str.substr(1);
        tmp.data = Error;
    }
    else{
        tmp.type = 1;
        tmp.data = stoi(str);
    }

    tmp.field = field;
    tmp.row = row;
    data[row][field] = tmp;
}

void CSVreader::ReadLine(string line){
    stringstream ss(line);
    string tmp;
    field = 0;
    while(getline(ss, tmp, ',')){
        Parse(row, field, tmp);
        field++;
    }
    row++;
}

bool issign(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<';
}

int CSVreader::GetVal(Data &d){
    // cout << d.row << " " << d.field;
    // if(d.type == 1) cout << " " << d.data << endl;
    // else cout << " " << d.str << endl;

    if(d.type == 1) return d.data;
    if(d.type == 0) return d.data = Error;
    if(d.type == 3) return Error;
    if(vis[d.row][d.field]) return d.data = Error;

    int x = 1, y = 1, n = d.str.length();
    int idx = 0;

    string s1, s2;
    if(d.str[0] == '-'){
        x = -1; idx++;
    }

    while(idx < n && !issign(d.str[idx])){
        s1 += d.str[idx];
        idx++;
    }

    char op = d.str[idx];
    idx++;

    if(d.str[idx] == '-'){
        y = -1; idx++;
    }

    while(idx < n){
        s2 += d.str[idx];
        idx++;
    }
    vis[d.row][d.field] = 1;

    if(isdigit(s1[0])){
        x *= stoi(s1);
    }
    else{
        Data a = data[stoi(s1.substr(1)) - 1][s1[0] - 'A'];
        if(a.type == 3) return d.data = Error;
        if(GetVal(a) == Error) return d.data = Error;
        x *= GetVal(a);
    }

    if(isdigit(s2[0])){
        y *= stoi(s2);
    }
    else{
        Data a = data[stoi(s2.substr(1)) - 1][s2[0] - 'A'];
        if(a.type == 3) return d.data = Error;
        if(GetVal(a) == Error) return d.data = Error;
        y *= GetVal(a);
    }

    if(abs(x) > Max || abs(y) > Max)    return d.data = Error;

    vis[d.row][d.field] = 0;

    if(op == '+'){
        if(abs(x + y) > Max) return d.data = Error;
        return d.data = x + y;
    }
    else if(op == '-'){
        if(abs(x - y) > Max)    return d.data = Error;
        return d.data = x - y;
    }
    else if(op == '*'){
        if(abs(x*y) > Max)   return d.data = Error;
        return d.data = x * y;
    }
    else if(op == '/'){
        if(y == 0) return d.data = Error;
        return d.data = x / y;
    }
    else if(op == '>'){
        d.type = 3;
        return d.data = x > y;
    }
    else if(op == '<'){
        d.type = 3;
        return d.data = x < y;
    }
    return d.data = Error;
}

void CSVreader::ParseData(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < field; j++){
            if(data[i][j].type == 2){
                GetVal(data[i][j]);
            }
        }
    }
}

void CSVreader::PrintData(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < field; j++){
            if(data[i][j].type == 0){
                cout << data[i][j].str;
            }
            else if(data[i][j].type == 1){
                cout << data[i][j].data;
            }
            else if(data[i][j].type == 3){
                cout << (data[i][j].data ? "true" : "false");
            }
            else{
                if(abs(data[i][j].data) == Error)    cout << "ERROR";
                else cout << data[i][j].data;
            }
            if(j != field - 1)  cout << ",";
        }
        cout << endl;
    }
}

signed main(){
    nono_is_handsome
    
    CSVreader reader;
    string tmp;
    while(getline(cin, tmp)){
        reader.ReadLine(tmp);
    }

    reader.ParseData();
    reader.PrintData();

    return 0;
}