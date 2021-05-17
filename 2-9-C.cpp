#include <iostream>
#include <vector>

int main() {
    long long  INF = 10e4;
    std::vector<std::vector<std::vector<int>>> dp;
    int n;
    std::cin >> n;
    // Создание пустого ДП
    for (int i = 0; i < n + 1; ++i) {
        dp.push_back(std::vector<std::vector<int>>());
        for (int j = 0; j < n + 1; ++j) {
            dp[i].push_back(std::vector<int>());
            for (int p = 0; p < n + 1; ++p) {
                dp[i][j].push_back(INF);
            }
        }
    }

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            std::cin >> dp[i][j][0];
        }
    }

    for (int k = 1; k < n + 1; ++k) {
        for (int i = 1; i < n + 1; ++i) {
            for (int j = 1; j < n + 1 ; ++j) {
                dp[i][j][k] = std::min(dp[i][j][k - 1], dp[i][k][k - 1] + dp[k][j][k - 1]);
            }
        }
    }
        /*
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << dp[i][j][k] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n' << '\n';
    }
         */

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n +  1; ++j) {
            std::cout << dp[i][j][n] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
