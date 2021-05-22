#include <iostream>

struct Matrix {
    unsigned long long array[5][5];
    Matrix() {
        for (int i = 0; i < 5; ++i) {
            for(int j = 0; j < 5; ++j) {
                array[i][j] = 1;
            }
        }

        array[3][2] = 0;
        array[3][4] = 0;
        array[4][2] = 0;
        array[4][4] = 0;
    }
    Matrix(int) {
        for (int i = 0; i < 5; ++i) {
            for(int j = 0; j < 5; ++j) {
                array[i][j] = 0;
                if (i == j) {
                    array[i][j] = 1;
                }
            }
        }
    }

    Matrix& operator=(const Matrix& value) {
        for (int i = 0; i < 5; ++i) {
            for(int j = 0; j < 5; ++j) {
                array[i][j] = value.array[i][j] % 999999937;
            }
        }
        return *this;
    }

    friend Matrix operator*(const Matrix& left, const Matrix& right);// Friend для структуры.....
    friend Matrix operator%(const Matrix& left, const long long& right);



};
Matrix operator*(const Matrix& left, const Matrix& right) {
    Matrix ans;
    for (int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            unsigned long long sum = 0;
            for (int p = 0; p < 5; ++p) {
                sum = (sum + (left.array[i][p] * right.array[p][j]) % 999999937) % 999999937;
            }
            ans.array[i][j] = sum % 999999937;
        }
    }
    return ans;
}
Matrix operator%(const Matrix& left, const unsigned long long& right) {
    Matrix copy = left;
    for (int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            copy.array[i][j] = copy.array[i][j] % 999999937;
        }
    }
    return copy;

}

Matrix toDeg(Matrix val, unsigned long long deg) {
    unsigned long long md = 999999937;
    Matrix ans(1);
    Matrix p = val;
    while (deg) {
        if (deg & 1) {
            ans = ans % md;
            p = p % md;
            ans = (ans * p) % md;
        }
        p = (p*p) % md;
        p = p % md;
        deg >>= 1;
    }

    return ans;
}

int main() {
    unsigned long long n = 0;
    std::cin >> n ;
    while (n != 0) {
        Matrix G;
        G = toDeg(G, n - 1);
        unsigned long long sum = 0;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                sum = (sum + G.array[i][j]) % 999999937;
            }
        }
        std::cout << sum << '\n';
        std::cin >> n;
    }
    return 0;
}
