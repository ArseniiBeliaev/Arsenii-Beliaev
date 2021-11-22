#include <iostream> 
#include <vector>
#include <string>

std::vector<int> z_function(std::string& str) {
    std::vector<int>z_answer(str.size());
    int n = str.size();
    int left = - 1;
    int right = - 1;
    for (int i = 1; i < n; ++i) {
        if (left <= i && i <= right) {
           z_answer[i] = std::min(z_answer[i-left],right - i + 1);
        }
        while (i + z_answer[i] < n && str[z_answer[i]] == str[i+z_answer[i]]) {
           ++z_answer[i];
        }
        if (i + z_answer[i] - 1 > right ) {
            left = i; 
            right =  i + z_answer[i] - 1;
        }
    }
    return z_answer;
}
template <typename T>
void print(const T& object) {
    auto it = object.begin();
    while(it != object.end()) {
        std::cout << *it << ' ';
        ++it;
    }
}

int main() {
    std::string a; 
    std::cin >> a;
    print(z_function(a));
    return 0;
}
