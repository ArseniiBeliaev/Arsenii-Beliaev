#include <iostream>
#include <set>
#include <iterator>
#include <map>


class SetOfSet {
    std::set <long long>* global_set[100000];
    std::map <long long ,std::set <long long> > array;
    long long lot_lot;
public:

    SetOfSet(long long lot_lot):lot_lot(lot_lot) { // Так проще уудалять потом и ошибок не получать
        for ( long long i = 0 ; i < lot_lot+1 ; ++i  ) {
            global_set[i] = new std::set <long long>;
        }

    }

    void add(long long number , long long value) {
        (*global_set[number]).insert(value);
        (array[value]).insert(number);
    }
    void prt(long long number) {
        if (!((*global_set[number]).empty())) {
            for ( std::set <long long> :: iterator it = (*global_set[number]).begin(); it != (*global_set[number]).end() ; it++ ) {
                std::cout << *it << ' ';
            }
            std::cout << '\n';

        }
        else std::cout << "-1" << '\n';

    }
    void dlt(long long number , long long value) {
        (*global_set[number]).erase(value);
        (array[value]).erase(number);
    }
    void clr (long long number ) {
        std::set <long long> :: iterator it = (*global_set[number]).begin();
        while ( it != (*global_set[number]).end() ) {
            (array[*it]).erase(number);
            ++it;
        }
        delete global_set[number];
        global_set[number] = new std::set <long long>;

    }

    void prtNum( long long size , long long value ) {
        if ( array[value].empty() ) {
            std::cout << "-1";
            std::cout << '\n';
        }
        else {
            for ( std::set <long long> :: iterator it = (array[value]).begin(); it != (array[value]).end() ; it++ ) {
                std::cout << *it << ' ';
            }
            std::cout << '\n';
        }
    }
    ~SetOfSet() {
        for (long long i = 0; i < lot_lot + 1; ++i) {
            delete global_set[i];
        }
    }
};
int main() {

    long long n , m , k;
    long long x , y;
    std::cin >> n >> m >> k;
    std::string command;
    SetOfSet Set(m);

    for (long long i = 0 ; i < k ; ++i ) {
        std::cin >> command;
        if ( command == "ADD") {
            std::cin >> x >> y;
            Set.add(y,x);

        }
        if ( command == "DELETE") {
            std::cin >> x >> y;
            Set.dlt(y,x);
        }
        if (command == "CLEAR" ) {
            std::cin >> y;
            Set.clr(y);
        }
        if (command == "LISTSET" ) {
            std::cin >> y;
            Set.prt(y);
        }
        if ( command == "LISTSETSOF") {
            std::cin >> y;
            Set.prtNum(m,y);
        }
    }
    return 0;
}
