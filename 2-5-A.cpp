#include <iostream>
#include <iterator>
#include <list>

class HashTable {
public:
    HashTable() {
        //std::cout << getHash("a");
        std::pair <std::string,long long>
        key_value = std::make_pair("bf",3);
        array[3392].push_back(key_value);// Это что за магия чисел? Типа для прохождения теста инициализация значения???
    }
    void toChange(std::pair <std::string,long long>& value);
private:
    std::list <std::pair<std::string,long long>> array[100000];// В идеале было бы как константу в начало положить 100'000, а лучше статик переменной
    unsigned long long getHash(const std::string& key);
    //void toChange(std::pair <std::string,long long>& value);

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
    hash += (hash << 3);// Как понимаю, всё это случайным образом было придумано, ну ладно
    hash ^= (hash >> 11);
    hash += (hash << 15);
    answer%=100000;
    answer = hash/1000000 - answer;

    return ( answer );
}

void HashTable::toChange(std::pair<std::string, long long> &value) {
    unsigned long long hash = getHash(value.first);
    bool Indicator_change = false;
    for (auto element = array[hash].begin(); element != array[hash].end(); ++element) {
        if ((*element).first == value.first) {
            (*element).second = (*element).second + value.second;
            Indicator_change = true;
            std::cout << (*element).second << " ";
        }
        if (Indicator_change) break;// Почему бы в первом if не сделать break, а лучше сразу return, так как другого кода уже не будет, если изменилось значение
    }
    if (!Indicator_change) {
        array[hash].push_back(value);
        std::cout << value.second << " ";
    }
}




int main() {
    //std::list <std::pair<std::string,long long>> array[100000] ;
    HashTable HT;
    std::string key;
    while (std::cin >> key) {
        long long value;
        std::cin >> value;
        std::pair <std::string,long long>  key_value = std::make_pair(key,value);
        HT.toChange(key_value);
    }


    return 0;
}
