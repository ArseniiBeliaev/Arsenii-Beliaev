
#include <iostream>
#include <fstream>

long long int answer = 0;

void Merge_sort (long long int * array , long long int left , long long int right ) {
    long long int middle = (left + right)/2 ;
    long long int uk_1 = left ;
    long long int uk_2 = middle + 1 ;
    long long int *mrg = new long long int [100000];//Эту вещь можно создать один раз в более общей функции и потом несколько раз переиспользовать
    for( long long int j=left; j<=right; j++) {
        if ((uk_1 <= middle) && (( uk_2 > right ) || (array[uk_1] < array[uk_2]))) {
            mrg[j]=array[uk_1];
            uk_1++;
        }
        else {
            mrg[j]=array[uk_2];
            uk_2++;
            answer += middle - uk_1 + 1 ;
                
        }
    }
    
    for ( long long int j=left; j<=right; j++ ) {
    array[j]=mrg[j];
        
    }
    delete[]mrg;
    
}

void Merge_rec ( long long int * array , long long int left , long long int right ) {
    long long int middle = ( left + right ) / 2 ;
    if (left < right ) {
        
        Merge_rec ( array , left , middle );
        Merge_rec ( array , middle + 1 , right );
        Merge_sort ( array , left , right );
    }
}

 int main() {
    std::ifstream f_input  ("inverse.in");
    std::ofstream f_output ("inverse.out");
    long long  int size = 0 ;
    f_input >> size;
    long long  int array[size] ;
    for (long long int i = 0; i < size ; ++i ) {
        f_input >> array[i] ;
    }
    Merge_rec(array, 0, size - 1 );
    f_output << answer << '\0';
    f_output.close();
    f_input.close();
    return 0;
}

