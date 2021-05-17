#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;
    char array[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> array[i][j];
        }
    }
    int m = ( 1 << n );
    long long dp[m];

    for (int i = 0; i < m; ++i) {
        dp[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int mask_old = i;
        int node = 0;
        while(node < n) {
            if ((mask_old & (1 << node)) != 0) {
                int mask_clean = (mask_old ^ (1 << node));
                for (int j = 0; j < n; ++j) {
                    if (array[node][j] == 'Y' && (mask_clean & (1 << j)) == 0) {
                       int mask_node = (1 << node);
                       int mask_j = (1 << j);
                       int mask_new = (mask_clean | mask_node | mask_j);
                       dp[mask_new] = std::max(dp[mask_new], dp[mask_clean] + 2);
                    }
                }
            }
            node++;
        }
    }

    //std::cout << "\n";

    std::cout << dp[m-1];
}
