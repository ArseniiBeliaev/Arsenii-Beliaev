

#include <iostream>
#include <deque>

struct buffer {
    void check() {
        while ( buffer_right.size() < buffer_left.size()) {
        buffer_right.push_front(buffer_left.back());
        buffer_left.pop_back();
        }
        
        while (buffer_left.size() < buffer_right.size()) {
        buffer_left.push_back(buffer_right.front());
        buffer_right.pop_front();
            }
    }
    
    void push(int value) {
        check();
        buffer_right.push_back(value);
    }
    
    void vip_push(int value) {
        check();
        buffer_left.push_back(value);
    }
    
    int kick() {
        int value;
        
        check();
        value = buffer_left.front();
        buffer_left.pop_front();
        return value;
    }
private:
    std::deque<int> buffer_left;
    std::deque<int> buffer_right;
};

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
        
    int requestCount;
    int value;
    char cmd;
    
    buffer goblins;
    
    
    cin >> requestCount;
    
    while(requestCount --> 0) {
        cin >> cmd;
        if (cmd == '-'){
            cout << goblins.kick() << '\n';
            continue;
        }
        if (cmd == '+') {
            cin >> value;
            goblins.push(value);
            continue;
        }
        if (cmd == '*') {
            cin >> value;
            goblins.vip_push(value);
            continue;
        }
        
    }
    
    
    
    return 0;
}
