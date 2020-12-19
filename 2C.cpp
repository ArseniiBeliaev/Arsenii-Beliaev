#include <iostream>
#include <cstdio>
typedef long long ll;



int partition(int l,int r,long long* array) {
    int mid_val = array[(l+r)/2];
    while (l <= r) {
       while (array[l] < mid_val) ++l;
       while (array[r] > mid_val) --r;
       if (l >= r) break;
       std::swap(array[l],array[r]);
       ++l;
       --r;
    }
    return l;
}

long long findK(long long *array , long long array_size, long long  k) {
    int left = 0;
    int right = array_size-1;
    while (true) {
        int mid = partition(left,right,array);
        if (mid==k) {
            return array[k];
        }
        if (mid < k) {
            left = mid+1;
        }
        else {
            right = mid-1;
        }
    }
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

