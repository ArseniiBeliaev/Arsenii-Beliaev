#include <iostream>
#include <algorithm>

long long big(long long deg) {
    long long answer = 1;
    for (long long i = 0; i < deg; ++i) {
        answer = answer * 2;
    }
    return answer;
}
int main() {
    long long answer;
    answer = 0;
    long long num;
    std::cin >> num;
    long long items[num];
    for (long long i = 0; i < num; ++i) {
        std::cin >> items[i];
    }
    long long bag;
    std::cin >> bag;
    long long dp[big(num/2)];
    for (long long i = 0; i < big(num/2); ++i) {
        dp[i] = bag;
        for (long long j = 0; j < num / 2; ++j) {
            if ((i & big(j)) != 0) {
                dp[i] -= items[j];
            }
        }
    }
    std::sort(dp,dp+big(num / 2));
    for (long long i = 0; i < big(num / 2 + num % 2); ++i ) {
        long long  res = 0;
        for (long long j = 0; j < num / 2 + num % 2; ++j) {
            if ((i & (big(j))) != 0) {
                res += items[j + num / 2];
            }
        }
        auto it = std::upper_bound(dp, dp + big(num/2), res-1);
        answer += dp + big(num / 2) - it;
    }
    std::cout << answer;
    return 0;
}
