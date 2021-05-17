#include <iostream>

int main() {
    long long n;
    long long m;
    std::cin >> n >> m;
    int array[n+1][m+1];
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            array[i][j] = 0;
        }
    }
    for (int i = 1; i < m + 1; ++i) {
        int x = 0;
        int y = 0;
        std::cin >> x >> y;
        array[x][i] = 1;
        array[y][i] = 1;
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
