#include<bits/stdc++.h>
using namespace std;
#define nono_is_handsome cin.tie(0); ios_base::sync_with_stdio(0);
#define int long long
const int Field = 30;
const int Row = 1005;
const int Error = -1e9;
const int Max = 10000000;
typedef struct Data{
    int type;   // 0: string, 1: int, 2: equation, 3: bool
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
    }
    void ReadLine(string line);
    void PraseData();
    void PrintData();
    int GetVal(Data &d);
private:
    Data data[Field][Row];
    bool vis[Field][Row];
    int field;
    int row = 0;
};

Data Prase(string str){
    Data tmp;
    if(str[0] == '#'){
        tmp.type = 0;
        tmp.str = str.substr(1);
    }
    else if(str[0] == '='){
        tmp.type = 2;
        tmp.str = str.substr(1);
    }
    else{
        tmp.type = 1;
        tmp.data = stoi(str);
    }
    return tmp;
}

void CSVreader::ReadLine(string line){
    stringstream ss(line);
    string tmp;
    field = 0;
    while(getline(ss, tmp, ',')){
        data[row][field] = Prase(tmp);
        data[row][field].row = row;
        data[row][field].field = field;
        field++;
    }
    row++;
}

int CSVreader::GetVal(Data &d){
    // cout << d.row << " " << d.field;
    // if(d.type == 1) cout << " " << d.data << endl;
    // else cout << " " << d.str << endl;

    if(d.type == 1) return d.data;
    if(d.type == 0) return d.data = Error;
    if(vis[d.row][d.field]) return d.data = Error;

    int x = 1, y = 1, n = d.str.length();
    int idx = 0;

    string s1, s2;
    if(d.str[0] == '-'){
        x = -1; idx++;
    }

    while(d.str[idx] != '+' && d.str[idx] != '-' && d.str[idx] != '*' && d.str[idx] != '/' && d.str[idx] != '>' && d.str[idx] != '<' && idx < n){
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

void CSVreader::PraseData(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < field; j++){
            if(data[i][j].type == 2){
                data[i][j].data = GetVal(data[i][j]);
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
                if((data[i][j].data) == Error)    cout << "ERROR";
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

    reader.PraseData();
    reader.PrintData();
}