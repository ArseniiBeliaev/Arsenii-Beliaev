#include <iostream>

bool Bit(long long mask, int pos) {
    return ((mask & (1 << pos)) >> pos) == 1;
}

bool IsSquareCorrect(long long mask_f, long long mask_s, int pos) {
    return !(Bit(mask_f, pos) == Bit(mask_f,pos + 1) &&
            Bit(mask_f,pos) == Bit(mask_s,pos) &&
            Bit(mask_s,pos) == Bit(mask_s,pos + 1));
}

bool correct(long long mask_f, long long mask_s, int m) {
    for (int i = 0; i < m - 1; ++i) {
        if (!IsSquareCorrect(mask_f, mask_s, i)) {
            return false;
        }
    }

    return true;
}


int main() {
    int n = 0;
    int m = 0;
    std::cin >> m >> n;
    if (n > m) std::swap(m,n);
    long long ma = ( 1 << n);
    long long dp[ma][m];// В данном случае у тебя зависимость только между двумя соседними столбцами и можно было обойтись только массивом на 2 строки
    for (int i = 0; i < ma; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = 0;
            if (j == 0) {
                dp[i][j] = 1;
            }
        }
    }

    for (int j = 0; j < m - 1; ++j) {
        for (long long mask_old = 0; mask_old < ma; ++mask_old) {
            for (long long mask_new = 0; mask_new < ma; ++mask_new) {
                if (correct(mask_old,mask_new,n)) {
                    dp[mask_new][j + 1] += dp[mask_old][j];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < ma; ++i) {
        ans += dp[i][m-1];
    }

    std::cout << ans;
    return 0;
}
