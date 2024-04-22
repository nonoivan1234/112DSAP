#include<bits/stdc++.h>
using namespace std;
#define nono_is_handsome cin.tie(0); ios_base::sync_with_stdio(0);
#define int long long

typedef struct Data{
    int a = 0;
    char op = ' ';
} Data;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void print(stack<int> st){
    stack<int> temp = st;
    while(!temp.empty()){
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

void print(vector<Data> v){
    for(auto x: v){
        if(x.op == ' ') cout << x.a << " ";
        else cout << x.op << " ";
    }
    cout << endl;
}

int precedence(char c){
    if(c == '^') return 3;
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

int calc(int a, int b, char op){
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/'){
        if(b == 0) return 0;
        return a / b;
    }
    if(op == '^'){
        if (b > 0) return pow(a, b);
        if (b == 0){
            if (a >= 0) return 1;
            return -1;
        }
        return 0;
    }
    return 0;
}

int eval(string s){
    vector<Data> infix;

    int n = s.size(), i = 0;
    while(i < n){
        Data d;
        if(s[i] == '('){
            d.op = s[i];
            i++;
        }
        else if(s[i] == ')'){
            d.op = s[i];
            i++;
        }
        else if(isOperator(s[i])){
            d.op = s[i];
            i++;
        }
        else{
            string num = "";
            while(i < n && isdigit(s[i])){
                num += s[i];
                i++;
            }
            d.a = stoll(num);
        }

        infix.push_back(d);
    }

    // Consider negative numbers
    for(int i = 0; i < infix.size() - 1; i++){
        if(infix[i].op == '-' && (i == 0 || isOperator(infix[i-1].op))){
            infix[i+1].a *= -1;
            infix.erase(infix.begin() + i);
        }
    }

    for(int i = 1; i < infix.size() - 1; i++){
        if (infix[i].op == '-' && infix[i-1].op == '('){
            infix[i+1].a *= -1;
            infix.erase(infix.begin() + i);
        }
    }


    stack<Data> st;
    vector<Data> postfix;

    for(auto x: infix){
        if(x.op == ' '){
            postfix.push_back(x);
        }
        else if(x.op == '('){
            st.push(x);
        }
        else if(x.op == ')'){
            while(!st.empty() && st.top().op != '('){
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty() && precedence(st.top().op) >= precedence(x.op)){
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(x);
        }
    }

    while(!st.empty()){
        postfix.push_back(st.top());
        st.pop();
    }

    // Evaluate postfix
    stack<int> evalStack;
    for(auto x: postfix){
        if(x.op == ' '){
            evalStack.push(x.a);
        }
        else{
            int b = evalStack.top();
            evalStack.pop();
            int a = evalStack.top();
            evalStack.pop();
            int result = calc(a, b, x.op);
            evalStack.push(result);
        }
    }
    int result = evalStack.top();
    evalStack.pop();

    return result;
}

signed main(){
    nono_is_handsome
    
    string s;
    while(cin >> s){
        // replace "**" to "^"
        for(int i = 0; i < s.size() - 1; i++){
            if(s[i] == '*' && s[i+1] == '*'){
                s[i] = '^';
                s.erase(s.begin() + i + 1);
            }
        }

        cout << eval(s) << endl;
    }

    return 0;
}