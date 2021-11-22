#include <iostream> 
#include <vector>
#include <string> 
#include <stack>

//camelCase
//PascalCase
//snake_case

void Sorting(std::vector<std::pair<size_t, size_t> >& buffer_panswer, std::vector<size_t>& panswer) {
    std::vector <size_t> cnt(400001);
    std::vector <size_t> cntt(400001);
    std::vector<std::pair<size_t, size_t> > copy_buffer_panswer = buffer_panswer;
    // for (size_t i = 0; i < copy_buffer_panswer.size(); ++i) {
    //     std::cout << copy_buffer_panswer[i].first << " " << copy_buffer_panswer[i].second << '\n';
    // }
    for (size_t i = 0; i < buffer_panswer.size(); ++i) {
        ++cnt[buffer_panswer[i].first];
    }
    for (size_t i = 1; i < 400001; ++i) {
        cnt[i] += cnt[i-1];
    }
    for (int i = buffer_panswer.size() - 1; i >= 0; --i) {
        panswer[--cnt[buffer_panswer[i].first]] = i;
    }
    
    for (size_t i = 0; i < panswer.size(); ++i) {
        copy_buffer_panswer[i] = buffer_panswer[panswer[i]];
    }

    // for (size_t i = 0; i < copy_buffer_panswer.size(); ++i) {
    //      std::cout << copy_buffer_panswer[i].first << " " << copy_buffer_panswer[i].second << '\n';
    // }
}


void Sort(std::vector<std::pair<size_t, size_t> >& classes, std::vector<size_t>& panswer) {
    size_t size = panswer.size();
    std::vector<std::pair<size_t, size_t> > classes_copy = classes;

    // for (size_t i = 0; i < size; ++i) {
    //     std::cout << "< " << classes[i].first << " " << classes[i].second << " >\n";
    // }

    std::vector<size_t> count(size);
    std::vector<size_t> temp(size);


    count.assign(size, 0);
    for (size_t i = 0; i < size; ++i) {
        ++count[classes[i].second];
    }
    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }
    for (size_t i = size; 0 < i; --i) {
        temp[--count[classes[i - 1].second]] = i - 1;
    }

    count.assign(size, 0);
    for (size_t i = 0; i < size; ++i) {
        ++count[classes[i].first];
    }
    for (size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }
    for (size_t i = size; 0 < i; --i) {
        panswer[--count[classes[temp[i - 1]].first]] = temp[i - 1];
    }

    for (size_t i = 0; i < panswer.size(); ++i) {
        classes[i] = classes_copy[panswer[i]];
    }
}

void FillNewClases(std::vector<std::pair<size_t, size_t> >& buffer_panswer, std::vector<size_t>& classes, std::string& str) {
    classes[0] = 0;
    for (size_t i = 1; i < buffer_panswer.size(); ++i) {
        if (buffer_panswer[i] == buffer_panswer[i-1]) {
            classes[i] = classes[i-1];
            continue;
        }
        classes[i] = classes[i-1] + 1;
    }
}

void FillNewClassesChar(std::vector<size_t>& panswer, std::vector<size_t>& classes, std::string& str) {
    classes[0] = 0;
    for (size_t i = 1; i < panswer.size(); ++i) {
        if (str[panswer[i]] == str[panswer[i-1]]) {
            classes[i] = classes[i-1];
            continue;
        }
        classes[i] = classes[i-1] + 1;
    }
}

void FillRow(std::vector<size_t>& panswer) {
    for (size_t i = 0; i < panswer.size(); ++i) {
        panswer[i] = i;
    }
}

void BaseCalculate(std::vector<size_t>& panswer, std::vector<size_t>& classes, std::string& str) {   
    FillRow(panswer);
    std::vector <size_t> cnt(256);
    for (size_t i = 0; i < str.size(); ++i) {
        ++cnt[str[i]];
    }
    for (size_t i = 1; i < 256; ++i) {
        cnt[i] += cnt[i-1];
    }
    for (int i = str.size() - 1; i >= 0; --i) {
        panswer[--cnt[str[i]]] = i;
    } 
    FillNewClassesChar(panswer,classes,str);
}

void ReCalculate(std::vector<size_t>& panswer, std::vector<size_t>& classes, std::string& str, int power_bit) {
    size_t shift = str.size();
    std::vector<std::pair<size_t,size_t> > buffer_panswer(str.size()); 
    for (size_t i = 0; i < panswer.size(); ++i) {
        buffer_panswer[panswer[i]].first = classes[i];
        // Решить panswer[i] = (x + 2^(k-1) % shift) - т/е когда panaswer[i] - это середина (second), а не начало
        int j = panswer[i];
        j -= power_bit/2;
        while (j < 0)
        {
            j += shift;
        }
        buffer_panswer[j].second = classes[i];
    }
    FillRow(panswer);
    // отсортить его и paanswer "связно"
    Sort(buffer_panswer, panswer);
    FillNewClases(buffer_panswer,classes,str); 
}

std::vector<size_t> GetSuffixArray(std::string str) {
    str += "#";
    size_t power_bit = 1; 
    std::vector <size_t> classes(str.size());
    std::vector <size_t> panswer(str.size());
    BaseCalculate(panswer,classes,str);
    for (;power_bit < str.size(); power_bit *= 2) {
        ReCalculate(panswer,classes,str,power_bit);
    } 
    ReCalculate(panswer,classes,str,power_bit);
    return panswer;
} 
/*
/ В panswer хранятся отсоортированные начала каждый строки i , i + 2 ^ k - 1
/
*/


int main() {
    //std::string str = "abacabcd";
    std::string str; 
    std::cin >> str;
    std::vector <size_t> panswer = GetSuffixArray(str);
    for (size_t i = 1; i < panswer.size(); ++i) {
         std::cout << panswer[i] + 1 << ' ';
    }
    // std::vector <size_t> classes(str.size());
    // std::vector <size_t> panswer(str.size());
    // BaseCalculate(panswer,classes,str);
    // ReCalculate(panswer,classes,str,2);
    // // for (size_t i = 0; i < panswer.size(); ++i) {
    // //     std::cout << panswer[i] << " class " << classes[i] << '\n';
    // // }
    // ReCalculate(panswer,classes,str,4);
    // ReCalculate(panswer,classes,str,8);
    // ReCalculate(panswer,classes,str,16);
    // for (size_t i = 0; i < panswer.size(); ++i) {
    //     std::cout << panswer[i] << " class " << classes[i] << '\n';
    // }
    return 0; 
}
