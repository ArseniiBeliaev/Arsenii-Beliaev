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

class myStack {
public:

    node *stc = nullptr;
    int size = 0;

    myStack() {

    }

    void push(ll x) {
        node *v = new node(x);
        v->prev = stc;
        stc = v;
        ++size;
        cout << "ok" << endl;
    }

    void back() {
        int bac;
        if (stc == nullptr) {
            cout << "error" << endl;
        } else {
            bac = stc->val;
            cout << bac << endl;
        }
    }

    void pop() {
        if (stc == nullptr) {
            cout << "error" << endl;
        } else {
            cout << stc->val << endl;

            node* buf = stc->prev;
            delete stc;
            stc = buf;
            size = size - 1;
        }
    }

    void clear() {
        while (stc != nullptr) {
            node* buf = stc->prev;
            delete stc;
            stc = buf;
        }

        size = 0;
    }
};

int main(){
    bool b = true;
    string cmd;
    int x;
    myStack bob;
    while (b) {
        cin >> cmd ;
        if ( cmd == "exit"){
            cout << "bye" << endl;
            b = false;

        }
        if ( cmd == "back" ){
            bob.back();
        }
        if ( cmd == "push"){
            cin >> x ;
            bob.push(x);
        }
        if ( cmd == "pop")
            bob.pop();
        if ( cmd == "clear" ){
            bob.clear();
            cout << "ok" << endl;
        }
        if ( cmd == "size" ){
            cout << bob.size << endl ;
        }
    }
    return 0;
}
