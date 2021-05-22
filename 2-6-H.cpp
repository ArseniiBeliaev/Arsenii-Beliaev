#include <iostream>

int main() {
    long long size_1;
    long long size_2;
    std::cin >> size_1;
    std::cin >> size_2;
    
    long long array_1[size_1];
    long long array_2[size_2];
    long long array_small[std::min(size_2,size_1)+1];
    for (long long i =0; i < std::min(size_2,size_1)+1; ++i) {
        array_small[i] = -1;
    }
    
    for (long long i = 0; i < size_1; ++i) {
        std::cin >> array_1[i];
    }
    for (long long i = 0; i < size_2; ++i) {
        std::cin >> array_2[i];
    }

    long long dp[size_1+1][size_2+1];// Аналогично, можно вынести и сделать всё более читаемо
    for (long long i = 0; i < size_1 + 1; ++i) {
        for (long long j = 0; j < size_2 + 1; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i < size_1 + 1; ++i) {
        long long best = 0;
        long long ind = 0;
        for (long long j = 1; j < size_2 + 1; ++j) {
            if (array_1[i-1] == array_2[j-1]) {
                for ( long long l = ind + 1; l < j; ++l) {
                     if (dp[i-1][l] > dp[i-1][best] && array_2[l-1] < array_1[i-1]) {
                        best = l;
                    }
                    ind = l;
                }
                dp[i][j] = dp[i-1][best] + 1;
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }
        
    }
    int answer = 0;

    for (int i = 0; i < size_2 + 1; ++i) {
        if (answer < dp[size_1][i]) {
            answer = dp[size_1][i];
        }
    }
    std::cout << answer;


    return 0;
}
