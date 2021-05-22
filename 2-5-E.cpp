#include <iostream>
#include <iterator>
#include <list>

class HashTable {
public:
    void toChange(std::pair <std::string, std::string>& value);
    void get(std::string key);
    void remove(std::string key);
private:
    std::list <std::pair<std::string,std::string>> array[100000];
    unsigned long long getHash(const std::string& key);

};

unsigned long long HashTable::getHash(const std::string& key) {
    unsigned int hash = 0;
    long long answer = 1000000000;

    for (int i=0; i < key.size(); ++i)
    {
        hash += (unsigned char)(key[i]);
        //std::cout << hash << " ";
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    answer%=100000;
    answer = hash/1000000 - answer;

    return ( answer );
}

void HashTable::toChange(std::pair<std::string, std::string> &value) {
    unsigned long long hash = getHash(value.first);
    bool Indicator_change = false;
    for (auto element = array[hash].begin(); element != array[hash].end(); ++element) {
        if ((*element).first == value.first) {
            (*element).second = value.second;
            Indicator_change = true;
            //std::cout << (*element).second << " ";
        }
        if (Indicator_change) break;
    }
    if (!Indicator_change) {
        array[hash].push_back(value);
        //std::cout << value.second << " ";
    }
}

void HashTable::get(std::string key) {// Корректнее было бы сделать функцию get, которая возвращает ссылку на элемент, а на её основе уже toChange, print и remove
    // А так получается копирование кода
    unsigned long long hash = getHash(key);
    bool Indicator_in = false;
    for (auto element = array[hash].begin(); element != array[hash].end(); ++element) {
        if ( (*element).first == key ) {
            std::cout << (*element).second << '\n';
            Indicator_in = true;
        }
        if (Indicator_in) break;
    }
    if (!Indicator_in) std::cout << "none" << '\n';
}

void HashTable::remove(std::string key) {
    unsigned long long hash = getHash(key);
    bool Indicator_in = false;
    for (auto element = array[hash].begin(); element != array[hash].end(); ++element) {
        if ( (*element).first == key) {
            array[hash].erase(element);
            Indicator_in = true;
        }
        if (Indicator_in) break;
    }
}




int main() {
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    HashTable hashTable;
    std::string command;
    std::string key;
    std::string value;
    while (std::cin >> command) {
        if (command == "delete" ) {
            std::cin >> key;
            hashTable.remove(key);
        }

        if ( command == "get" ) {
            std::cin >> key;
            hashTable.get(key);
        }

        if ( command == "put" ) {
            std::cin >> key >> value;
            std::pair <std::string, std::string> val;
            val = std::make_pair(key,value);
            hashTable.toChange(val);
        }
    }
    return 0;
}
