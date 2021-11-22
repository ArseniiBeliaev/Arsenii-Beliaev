#include <iostream>

void acceleeration() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}

long long divn = 1e9 + 7; 
const int N = 210000;
long long factorial[N];
long long rev[N];
long long expon(long long a, long long deg);
long long gcd (long long a, long long b, long long& x, long long& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

long long corrected(long long a) {
    a %= divn;
	while(a < 0)
		a += divn;
	return a;
}
void factorial_and_rev() {
    factorial[0] = 1;
    rev[0] = 1;
    for (size_t i = 1; i < N; ++i) {
        factorial[i] = (factorial[i-1] * i) % divn;
        rev[i] = (expon(factorial[i], divn - 2)) % divn;
    }
}

    

long long CNK(long long n, long long k) {
    return ((((factorial[n] * rev[k]) % divn) * rev[n-k]) % divn);
}

long long expon(long long a, long long deg) {
    long long result = 1;
	while(deg > 0) {
		if (deg & 1) result = (result * a) % divn;
		a = (a * a) % divn;
		deg >>= 1;
	}
	return result;
} 

long long Stirling(long long n, long long k) {
    long long sum = 0; 
    for(long long j = 1; j <= k; ++j) {
        long long deg = j + k;
        long long val = 1 - 2 * ((j + k) % 2);
        long long ckj = CNK(k,j);
        long long j_in_n = expon(j,n);
        sum =  corrected(sum + val * ckj * j_in_n);
    }
    return ((sum * rev[k]) % divn);
}


int main() {
    acceleeration();
    factorial_and_rev();
    long long n; 
    long long k;
    std::cin >> n >> k;
    long long answer = 0;
    long long a = Stirling(n,k); 
    long long b = Stirling(n-1,k);
    long long cf1 = a; 
    long long cf2 = ((n-1) * b) % divn;
    long long cf = corrected(cf1 + cf2);
    long long val;
    long long sum = 0;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> val;
        sum = corrected(sum + val);
    }
    answer = (sum * cf) % divn;
    std::cout << answer; 
    return 0;
}
