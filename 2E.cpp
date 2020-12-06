#include <iostream>
#include <vector>
 
 
typedef long long  ll;
 
class Heap {
 
    std::vector <std::pair<ll,ll>> HeapStorage;
    std::vector <ll> HeapStorageKey;
 
    void heapDown(ll index) {
        std::pair <ll,ll> temp;
        ll indexTemp;
        ll keyTemp;
        ll index_down_min = 0;
        ll index_up = index;
        ll index_down_1 = index_up * 2;
        ll index_down_2 = index_up * 2 + 1;
            if ( index_down_1 < HeapStorage.size() ) {
                if ( ((index_down_2) < HeapStorage.size()) && ( HeapStorage[index_down_2].first < HeapStorage[index_down_1].first )) {
                    index_down_1 = index_down_2;
                }
                if ( HeapStorage[index_down_1].first < HeapStorage[index_up].first ) {
 
                    indexTemp = HeapStorageKey[HeapStorage[index_down_1].second];
                    HeapStorageKey[HeapStorage[index_down_1].second] = HeapStorageKey[HeapStorage[index_up].second];
                    HeapStorageKey[HeapStorage[index_up].second] = indexTemp;
 
                    temp = HeapStorage[index_down_1];
                    HeapStorage[index_down_1] = HeapStorage[index_up];
                    HeapStorage[index_up] = temp;
                }
                heapDown(index_down_1);
            }
    }
 
    ll min(ll index_down_1 , ll index_down_2 ) {
        if ( HeapStorage[index_down_1].first < HeapStorage[index_down_2].first ) {
            return index_down_1 ;
        }
        else return index_down_2 ;
    }
 
    void heapUp( ll index ) {
        ll index_down = index;
        ll index_up = index_down / 2 ;
        ll indexTemp;
        ll keyTemp;
        std::pair <ll,ll> temp;
        if ( HeapStorage[index_down].first < HeapStorage[index_up].first && index_up != 0  ) {
 
            indexTemp = HeapStorageKey[HeapStorage[index_up].second];
            HeapStorageKey[HeapStorage[index_up].second] = HeapStorageKey[HeapStorage[index_down].second];
            HeapStorageKey[HeapStorage[index_down].second] = indexTemp;
 
            temp = HeapStorage[index_down];
            HeapStorage[index_down] = HeapStorage[index_up];
            HeapStorage[index_up] = temp;
 
 
            heapUp( index_up );
 
        }
 
 
    }
 
public :
 
    Heap() {
        HeapStorage.push_back(std::make_pair(0,0));
        HeapStorageKey.push_back (0);
    }
 
    void print() {
 
    }
 
    void insert (ll value, ll key) {
        long long itemSize;
        HeapStorage.push_back({value,key});
        itemSize=HeapStorage.size();
        HeapStorageKey.push_back(key);
        itemSize=HeapStorageKey.size();
        heapUp(key);
    }
 
    ll getMin() {
        return HeapStorage[1].first;
    }
 
    ll extraMin() {
        long long answer = HeapStorage[1].first;
        HeapStorage[1].first=HeapStorage[HeapStorage.size()-1].first;
        HeapStorage[1].second=HeapStorage[HeapStorage.size()-1].second;
        HeapStorage.pop_back();
        if (HeapStorage.size() > 1 ) { heapDown(1); }
        return answer;
    }
 
    void decreaseKey( ll gl_key , ll delta ) {
        ll position = HeapStorageKey[gl_key];
        HeapStorage[position].first = HeapStorage[position].first - delta;
        heapUp(position);
    }
 
};
void solve_1(Heap &heap){
    ll amou;
    ll q;
    ll d;
    char cmd[11];
    for (ll i = 0; i < 11; ++i) {
        cmd[i] = '0';
    }
    ll value;
    scanf("%lld", &amou);
    ll key = 1;
    for (ll i = 0; i < amou; ++i) {
        for (ll j = 0; j < 11; ++j) cmd[i] = 0;
        scanf("%s", cmd);
        if (cmd[0] == 'i') {
            scanf("%lld", &value);
            heap.insert(value, key);
            ++key;
        }
        if (cmd[0] == 'g') {
            printf("%lld\n", heap.getMin());
        }
        if (cmd[0] == 'e') {
            heap.extraMin();
        }
        if (cmd[0] == 'd') {
            scanf("%lld %lld", &q, &d);
            heap.decreaseKey( q,d );
        }
    }
}
int main() {
    Heap heap;
    ll N;
    ll K;
    ll value;
    ll key = 1;
    scanf("%lld %lld" , &N , &K );
    for ( ll i = 0 ; i < N ; ++i ) {
        scanf("%lld", &value );
        heap.insert(value,key);//Все подряд?
        ++key;
    }
    for (ll i = 0 ; i < K ; ++i ) {
        printf("%lld ", heap.extraMin());
    }
    return 0;
}
