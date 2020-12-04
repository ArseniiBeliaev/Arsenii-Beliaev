#include <iostream>
#include <cstdio>
typedef long long ll;



long long findK(long long *array , long long array_size, long long  k) {
    ll p = array[array_size / 2];
    ll *left = new ll[array_size];
    ll *right = new ll[array_size];
    ll left_size = 0, right_size = 0;
    for (ll i = 0 ; i < array_size; ++i) {
        if (array[i] < p) {
            left[left_size] = array[i];
            left_size++;
        } else if (array[i] > p) {
            right[right_size] = array[i];
            right_size++;
        }
    }
    ll equal = array_size - (left_size + right_size);
    if (left_size <= k && k < left_size + equal)
        return p;
    if (k < left_size)
         return findK(left, left_size, k);
    else 
         return findK(right, right_size, k - (left_size + equal));
    
}
int main() {
    ll size;
    ll k;
    scanf( "%lld" , &size);
    scanf( "%lld" , &k);
    ll array[size];
    for ( ll i = 0 ; i < size ; ++i ) {
        scanf("%lld", &array[i] );
    }
    printf("%lld",findK(array, size, k));
    return 0;
}

