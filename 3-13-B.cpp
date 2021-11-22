#include <iostream>
#include <vector> 


int main() {
    long long answer = 0; 
    long long simple = 0;
    long long n;
    std::cin >> n;
    std::vector <long long> primes;
    std::vector <long long> mind(n+1);
    for (size_t i = 2; i < mind.size(); ++i) {
        mind[i] = i;
    }
    for (size_t i = 2; i < mind.size(); ++i) {
        if (mind[i] == i) {primes.push_back(i);}
        for (size_t p = 0; p < primes.size() && primes[p] * i <= mind.size() && primes[p] <= mind[i]; ++p) {
            mind[primes[p]*i] = primes[p];
        }
    }

    for (size_t i = 3; i < mind.size(); ++i) {
        answer += mind[i];
    }

    for (size_t i = 1; i < primes.size(); ++i) {
        answer -= primes[i];
    }

    std::cout << answer;

    return 0;
}
