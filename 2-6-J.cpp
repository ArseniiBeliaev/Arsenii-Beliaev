#include <iostream>

int main() {
    long long bag;
    long long num;
    std::cin >> bag >> num;
    long long items[num+1];
    items[0] = 0;
    for (int i = 1; i < num + 1; ++i) {
        std::cin >> items[i];
    }
    // А дальше можно в функцию :(((
    long long dp[num+1][bag+1];// Кстати без восстановления ответа рюкзак можно на линейном массиве решать
    // Плюс рюкзак без ценностей (только с весами) можно решать на bool массивах, так как не нули будут как раз у взятых элементов... штрафануть бы тебя за всё это...
    for (int i = 0; i < num + 1 ; ++i) {
        for (int j = 0; j < bag + 1; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i < num + 1; ++i) {
        for (int j = 0; j < bag + 1; ++j) {
            dp[i][j] = std::max(dp[i-1][j],dp[i][j]);
            if (items[i] + j < bag + 1) {
                dp[i][j+items[i]] = std::max(dp[i][j+items[i]],dp[i-1][j] + items[i]);
            }
        }
    }

    long long max = 0;
    for (int i = 1; i < num + 1; ++i) {
        for (int j = 1; j < bag + 1; ++j) {
            if (max < dp[i][j]) {
                max = dp[i][j];
            }
        }
    }
    std::cout << max;

    return 0;
}
