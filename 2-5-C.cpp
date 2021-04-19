#include <iostream>
#include <cstdio>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    long long weight;
    long long high;
    long long number;
    long long x;
    long long y;
    long long sum = 0;
    std::cin >> weight >> high >> number;
    if (weight * high > 5000000) {
        for (long long i = 0; i < number; ++i) {
            std::cin >> x >> y;
        }
        std::cout << "NO";
    }
    else {
        long long array[high+1][weight+1];
        for (long long i = 1; i < high + 1; ++i ) {
            for (long long j = 1; j < weight + 1; ++j ) {
                array [i][j] = 0;
            }
        }
        /*
        for (long long i = 1; i < high + 1; ++i ) {
            for (long long j = 1; j < weight + 1; ++j ) {
                std:: cout << array [i][j] << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
         */
        for (long long i = 0; i < number; ++i) {
            std::cin >> x >> y ;
            if ( y > 0 && y < high + 1 && x > 0 && x < weight + 1) array[y][x] = 1;
            if ( y-1 > 0 && y-1 < high + 1 && x > 0 && x < weight + 1) array[y-1][x] = 1;
            if ( y+1 > 0 && y+1 < high + 1 && x > 0 && x < weight + 1)  array[y+1][x] = 1;
            if ( y > 0 && y < high + 1 && x+1 > 0 && x+1 < weight + 1) array[y][x+1] = 1;
            if ( y > 0 && y < high + 1 && x-1 > 0 && x-1 < weight + 1) array[y][x-1] = 1;
        }
        for (long long i = 1; i < high + 1; ++i ) {
            for (long long j = 1; j < weight + 1; ++j ) {
                sum+=array[i][j];
            }
        }
        if (sum == weight * high) {
            std::cout << "Yes";
        }
        else {
            std::cout << "No";
        }
    }
}
