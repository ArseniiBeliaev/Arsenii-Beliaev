#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <array>

// Нужно было реализовать используя бор - работает за О(длина текста), а  std::sort - за klogk * (длина самого длинного слова), k - число слов 
// Лучше разнести по отдельным функциям
int main() {
    std::string str;
    std::vector <std::string> words; 
    std::vector <std::string> points; 
    bool first_point = false;
    std::string point;
    std::string word;
    std::cin >> str;
    if (str[0] == '.') {
        first_point = true;
    }
    for (int i = 0; i < str.size();) {
        while (i < str.size() && str[i] == '.')
        {
            point += '.';
            ++i;
        }
        if (point.size()) {
            points.push_back(point);
        }
        point.clear();
        while ( i < str.size() && str[i] != '.')
        {
            word += str[i];
            ++i;
        }
        if (word.size()) {
            words.push_back(word);
        }
        word.clear();
    }  

    std::sort(words.begin(),words.end());
    int i = 0;
    int j = 0; 
    while (i != words.size() || j != points.size()) {
        if (first_point) {
            std::cout << points[j];
            first_point = false;
            ++j;
        }
        if (i < words.size()) {
            std::cout << words[i];
            ++i;
        }
        if (j < points.size()) {
            std::cout << points[j];
            ++j;
        }
    }
    return 0;   
}
