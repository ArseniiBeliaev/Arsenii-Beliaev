#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

class Heap {
    std::vector <std::pair<long long,long long>> heapStorage;
    ll heapStorage_key[1000000];

    int heapUp( ll indexDown ) {
        if ( indexDown == 0 ) return 0;
        ll indexUp = parent ( indexDown );
        if ( indexUp > -1 ) {
            if ( heapStorage[indexDown].first < heapStorage[indexUp].first ) {
                swap (indexDown,indexUp);
                heapUp(indexUp);
            }
        }
        return 0;
    }

    void heapDown ( ll indexUp ) {
        ll indexDown = indexUp * 2 + 1;
        if ( indexDown < heapStorage.size() ) {
            if ( (heapStorage[indexDown].first > heapStorage[indexDown + 1].first) && (indexDown + 1 < heapStorage.size()) ) {
                ++indexDown;
            }
            if ( heapStorage[indexDown].first < heapStorage[indexUp].first ) {
                swap(indexDown,indexUp);
                heapDown(indexDown);
            }

        }
    }

    ll parent ( ll indexDown ) {
        ll indexUp;
        if ( indexDown % 2 == 0 ) {
            indexUp = indexDown / 2 - 1;
        }
        if ( indexDown % 2 == 1 ) {
            indexUp = indexDown / 2 ;
        }
        return indexUp;
    }

    void swap ( ll index_1 , ll index_2 ) {
        ll req_1 = heapStorage[index_1].second;
        ll req_2 = heapStorage[index_2].second;
        ll tempIndex;
        std:: pair <ll,ll> temp;

        tempIndex=heapStorage_key[req_1];
        heapStorage_key[req_1]=heapStorage_key[req_2];
        heapStorage_key[req_2]=tempIndex;

        temp = heapStorage[index_1];
        heapStorage[index_1]=heapStorage[index_2];
        heapStorage[index_2]=temp;

    }


public:

    void insert (ll value , ll key ) {
        heapStorage.push_back({value,key});
        heapStorage_key[key]=heapStorage.size()-1;
        heapUp(heapStorage.size()-1);


    }

    ll getMin() {
        return heapStorage[0].first;
    }
    void extractMin() {

        /* std::cout << "WHILE EXTRCT " ;
        for ( auto x : heapStorage ) {
            std::cout << "value = " <<  x.first << " key = " << x.second << "  ";
        }
        std::cout << "\n" << "\n"; */

        swap(0,heapStorage.size()-1);
        ll index = heapStorage.size() - 1;
        ll req = heapStorage[index].second;
        heapStorage_key[req] = -3 ;
        heapStorage.pop_back();
        heapDown(0);

        /* std::cout << "AFTER EXTRCT " ;
        for ( auto x : heapStorage ) {
            std::cout << "value = " <<  x.first << " key = " << x.second << "  ";
        } */



    }
    void decreaseKey ( ll i , ll delta ) {
        ll req = i - 1 ;
        ll number = heapStorage_key[req];
        heapStorage[number].first = heapStorage[number].first - delta;
        heapUp(number);
    }

};

int main() {
    Heap heap;
    ll amou;
    ll q;
    ll d;
    char cmd[11];
    for (ll i = 0; i < 11; ++i) {
        cmd[i] = '0';
    }
    ll value;
    scanf("%lld", &amou);
    ll key = 0;
    for (ll i = 0; i < amou; ++i) {
        for (ll j = 0; j < 11; ++j) cmd[j] = 0;
        scanf("%s", cmd);
        if (cmd[0] == 'i') {
            scanf("%lld", &value);
            heap.insert(value, key);

        }
        if (cmd[0] == 'g') {
            printf("%lld\n", heap.getMin());
        }
        if (cmd[0] == 'e') {
            heap.extractMin();
        }
        if (cmd[0] == 'd') {
            scanf("%lld %lld", &q, &d);
            heap.decreaseKey(q, d);
        }
        ++key;
    }
    return 0;
}
