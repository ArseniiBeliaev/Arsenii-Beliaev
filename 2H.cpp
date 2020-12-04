#include <iostream>
typedef long long ll;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll size ;
    std::cin >> size;
    ll array[size];
    ll array2[size];
    ll index[10];
    ll ind;
    ll temp;
    ll p = 1;
    for ( ll i = 0 ; i < size ; ++i ) {
        std::cin >> array[i];
    }
    for (ll i = 0 ; i < 20 ; ++i ) {

        for ( ll z = 0 ; z < 10 ; ++z ) {
            index[z] = 0 ;
        }
        for ( ll z = 0 ; z < size ; ++z ) {
            array2[z] = 0 ;
        }

        for (ll j = 0 ; j < size ; ++j ) {
            ind = (array[j] / p ) % 10;
            ++index[ind];
        }
        ll delta = 1;
        for (ll j = 0 ; j < 10 ; ++j ) {
            if ( index[j] > 0 ) {
                temp = index[j];
                index[j] = delta;
                delta+=temp;
            }
        }

        for ( ll j = 0 ; j < size ; ++j ) {
            ind = ( array[j] / p ) % 10;
            if (index[ind] > 0 ) {
                array2[index[ind]-1] = array[j];
                ++index[ind];
            }
        }
        for ( ll j = 0 ; j < size ; ++j ) {
            array[j]=array2[j];
        }
        if (p >= 1e18)
            break;
        p=p*10;
    }
    for ( ll j = 0 ; j < size ; ++j ) {
        std::cout << array[j] << ' ';
    }
    return 0;
}
