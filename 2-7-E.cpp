#include <iostream>


struct Matrix {
    long long array[100][100];
    long long size = 0;
    Matrix(long long copy[100][100], long long size_c) {
        /*
        for (int i = 0; i < size_c; ++i) {
            for (int j = 0; j < size_c; ++j) {
                std::cout << copy[i][j] << " ";
            }
            std::cout << '\n';
        }
         */
        for (long long i = 0; i < size_c; ++i) {
            for (long long j = 0; j < size_c; ++j) {
                array[i][j] = copy[i][j];
            }
        }

        size = size_c;
    }
    Matrix(long long size_c) {
        for (long long i = 0; i < size_c; ++i) {
            for (long long j = 0; j < size_c; ++j) {
                array[i][j] = 0;
                if (i == j) {
                    array[i][j] = 1;
                }
            }
            size = size_c;
        }
    }

    friend Matrix operator*(const Matrix& left, const Matrix& right);
    friend Matrix operator%(const Matrix& left, const unsigned long long& right);

    Matrix& operator=(const Matrix& value) {
        for (int i = 0; i < value.size; ++i) {
            for(int j = 0; j < value.size; ++j) {
                array[i][j] = value.array[i][j] % 1000000007;
            }
        }
        size = value.size;
        return *this;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                std::cout << array[i][j] % 1000000007 << " ";
            }
            std::cout << "\n";
        }
    }

};

Matrix operator*( Matrix& left, Matrix& right) {
    Matrix ans(left.size);
    /*
    left.print();
    std::cout << "\n";
    right.print();
    std::cout << "\n";
     */
    for (long long i = 0; i < left.size; ++i) {
        for (long long j = 0; j < left.size; ++j) {
            unsigned long long sum = 0;
            for (long long p = 0; p < left.size; ++p) {
                sum = (sum + (left.array[i][p] * right.array[p][j]) % 1000000007) % 1000000007;
            }

            ans.array[i][j] = sum % 1000000007;
        }
    }
    //ans.print();
    //std::cout << "\n";
    //ans = left.size;
    return ans;
}

Matrix operator%(const Matrix& left, const unsigned long long& right) {
    Matrix copy(left.size);
    for (int i = 0; i < left.size; ++i) {
        for(int j = 0; j < left.size; ++j) {
            copy.array[i][j] = left.array[i][j] % 1000000007;
        }
    }
    return copy;
}








Matrix toDeg(Matrix& val, unsigned long long deg, long long size) {
    unsigned long long md = 1000000007;
    Matrix ans(size);
    Matrix p = val;
    //p.print();
    while (deg) {
        if (deg & 1) {
            //ans = ans % md;
            //p = p % md;
            ans = (ans * p) % md;
            //ans.print();
        }
        p = (p*p) % md;
        p = p % md;
        deg >>= 1;
    }
    return ans;
}


int main() {
    long long n;
    long long k;
    std::cin >> n >> k;
    long long array[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    long long mtrx[100][100];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mtrx[i][j] = 0;
            long long number = 0;
            long long save = (array[i] ^ array[j]);
            while (save != 0) {
                if (save & 1) {
                    number++;
                }
                save /= 2;
            }

            if ((number % 3 == 0)) {
                mtrx[i][j] = 1;
            }
        }
    }

    Matrix G(mtrx,n);
    //G.print();
    //G.print();
    G = toDeg(G,k-1,n);
    //G.print();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum = (sum + G.array[i][j]) % 1000000007;
        }
    }
    std::cout << sum;


    return 0;
}
