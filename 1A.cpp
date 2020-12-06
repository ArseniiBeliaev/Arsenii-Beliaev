#include <iostream>
#include <string>
using namespace std;
 
typedef long long ll;
 
struct node {
    int val;
    node *prev;
    node (ll n_val) {
        val = n_val;
        prev = nullptr;
    }
};
 
node *stc = nullptr;
int size = 0;
 
void push(ll x){
    node *v = new node(x);
    v -> prev = stc;
    stc = v;
    ++size;
    cout << "ok" << endl;
}

void back() {
    int bac;
    if (stc==nullptr) {
        cout << "error" << endl;
    }
    else {
    bac = stc -> val;
    cout << bac << endl ;
    }
}

void pop () {
    if (stc==nullptr) {
        cout << "error" << endl;
    }
    else {
    cout << stc -> val << endl;
    stc = stc -> prev;
    size = size - 1;
    }
}

void clear () {
    stc=nullptr;
    size=0;
}
 
 
int main(){
    bool b = true;
    string cmd;
    int x;
    while (b) {
        cin >> cmd ;
        if ( cmd == "exit"){
            cout << "bye" << endl;
            b = false;
            
        }
        if ( cmd == "back" ){
            back();
        }
        if ( cmd == "push"){
            cin >> x ;
            push(x);
        }
        if ( cmd == "pop")
            pop();
        if ( cmd == "clear" ){
            clear();
            cout << "ok" << endl; 
        }
        if ( cmd == "size" ){
            cout << size << endl ; 
        }
    }
    return 0;
}
