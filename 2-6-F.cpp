#include <iostream>
 
int main() {
    int size1;
    int size2;
    std::cin >> size1;
    int array1[size1+1];
    for (int i = 1; i < size1 + 1; ++i) {
        std::cin >> array1[i];
    }
 
    std::cin >> size2;
    int array2[size2+1];
    for (int i = 1; i < size2 + 1; ++i) {
        std::cin >> array2[i];
    }
 
 
    int array_ans[size1 + 1][size2 + 1];// Следующие 2 блока кода можно было бы и вынести в отдельную функцию из main
    for (int i = 0; i < size1 + 1; ++i) {
        for (int j = 0; j < size2 + 1; ++j) {
            array_ans[i][j] = 0;
        }
    }
 
   for (int i = 1; i < size1 + 1; ++i) {
       for (int j = 1; j < size2 + 1; ++j) {
           if (array1[i] != array2[j]) {
               array_ans[i][j] = std::max(array_ans[i][j-1],array_ans[i-1][j]);
           }
           else {
               array_ans[i][j] = array_ans[i-1][j-1]+1;
           }
       }
   }
 
 
 
    std::cout << array_ans[size1][size2] << '\n';
    return 0;
}
