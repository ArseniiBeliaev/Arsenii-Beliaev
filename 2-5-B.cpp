#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <cmath>

// 88956151
// 983

class HashTable {
public:

void swap(long long key_1, long long key_2);

private:

std::list <std::pair <long long, long long>> array[100000];

unsigned long long getHash(const int& key);

};

unsigned long long HashTable::getHash(const int &key) {
    long long x = 983;
    long long mod = 2679266343027533521;
    long long copy_key = key;
    unsigned long long hash = 0;
    long long i = 1;
    while (copy_key != 0 ) {
        hash += (long long)pow(x,i) *  ( copy_key % 10 );
        ++i;
        hash%=mod;
        copy_key/=10;
    }
    hash%=mod;
    hash%=100000;
    return hash;
}

void HashTable::swap(long long key_1, long long key_2) {
    long long hash_1 = getHash(key_1);
    long long hash_2 = getHash(key_2);
    bool Indicator_hash1_in = false;
    bool Indicator_hash2_in = false;
    auto element_key1 = array[hash_1].begin();
    auto element_key2 = array[hash_2].begin();

    for (auto element = array[hash_1].begin(); element != array[hash_1].end() ; ++element) {
        if ( (*element).first == key_1 ) {
            Indicator_hash1_in = true;
            element_key1 = element;
        }
        if (Indicator_hash1_in) break;
    }
    if (!Indicator_hash1_in) {
        std::pair <long long, long long> value = std::make_pair(key_1,key_1);
        array[hash_1].push_back(value);
        element_key1 = array[hash_1].end();
        --element_key1;
    }

    for (auto element = array[hash_2].begin(); element != array[hash_2].end(); ++element) {
        if ( (*element).first == key_2 ) {
            Indicator_hash2_in = true;
            element_key2 = element;
        }
        if (Indicator_hash2_in) break;
    }
    if (!Indicator_hash2_in) {
        std::pair <long long, long long> value = std::make_pair(key_2,key_2);
        array[hash_2].push_back(value);
        element_key2 = array[hash_2].end();
        --element_key2;
    }
    std::swap((*element_key1).second,(*element_key2).second);
    std::cout << std::abs((*element_key1).second - (*element_key2).second) << '\n';
}



int main() {
    HashTable hashTable;
    long long number;
    std::cin >> number;
    long long key1;
    long long key2;
    for (int i = 0; i < number; ++i) {
        std::cin >> key1 >> key2;
        hashTable.swap(key1,key2);
    }

}
