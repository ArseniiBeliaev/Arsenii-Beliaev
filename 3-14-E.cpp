#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
 
// 
//
 
struct Point
{
    long double x; 
    long double y;
    Point():x(0),y(0){}
    Point(long double x, long double y):x(x),y(y){}
    
};

std::istream& operator>> (std::istream &in, Point &point)
{
    in >> point.x;
    in >> point.y;
    return in;
}



int solve(const Point& a1, const Point& b1, const Point& a2, const Point& b2) {
    int TOresult = 0;
     long long  determinant = (b2.y - a2.y) * (a1.x - b1.x) - (b2.x - a2.x) * (a1.y - b1.y);
    if (determinant != 0 ) {
        long long k1 = ((b2.y - a2.y) * (b2.x - b1.x) - (b2.x - a2.x) * (b2.y - b1.y)) / determinant; 
        long long k2 = ((a1.x - b1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a1.y - b1.y)) / determinant; 
        if (std::abs(k1) <= 2 && std::abs(k2) <= 2) {
            long double c1 = ((b2.y - a2.y) * (b2.x - b1.x) - (b2.x - a2.x) * (b2.y - b1.y)) / determinant; 
            long double c2 = ((a1.x - b1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a1.y - b1.y)) / determinant;
            if (c1 >= 0 && c2 >= 0  && c1 <= 1  && c2 <= 1) {
                //std::cout << "YES"; 
                TOresult = 1;

            }
        }
        else {
            //std::cout << "NO"; 
            TOresult = 0;
        }
    }
    
    // Теперь проверим лежит ли хотя бы одно из начал первого отрезка на втором отрезке
    // Для этого воспользуемся параметрическим уравнением отрезка 
    long double result = std::sqrt((a2.x - b2.x) * (a2.x - b2.x) + (a2.y - b2.y) * (a2.y - b2.y));

    long double first = std::sqrt((a1.x - a2.x) * (a1.x - a2.x) + (a1.y - a2.y) * (a1.y - a2.y)); 
    long double second = std::sqrt((a1.x - b2.x) * (a1.x - b2.x) + (a1.y - b2.y) * (a1.y - b2.y));

    //std::cout << first << '\n' << second << '\n' << result; 
    if (std::abs(first + second - result) < 1e-8) {
        //std::cout << "YES"; 
        TOresult = 2;
    } 

    first = std::sqrt((b1.x - a2.x) * (b1.x - a2.x) + (b1.y - a2.y) * (b1.y - a2.y)); 
    second = std::sqrt((b1.x - b2.x) * (b1.x - b2.x) + (b1.y - b2.y) * (b1.y - b2.y));

    if (std::abs(first + second - result) < 1e-8) {
        //std::cout << "YES"; 
        TOresult = 2;
    } 

    result = std::sqrt((a1.x - b1.x) * (a1.x - b1.x) + (a1.y - b1.y) * (a1.y - b1.y));
    first = std::sqrt((a2.x - a1.x) * (a2.x - a1.x) + (a2.y - a1.y) * (a2.y - a1.y)); 
    second = std::sqrt((a2.x - b1.x) * (a2.x - b1.x) + (a2.y - b1.y) * (a2.y - b1.y));
    //std::cout << first << '\n' << second << '\n' << result; 
    if (std::abs(first + second - result) < 1e-8) {
        //std::cout << "YES"; 
        TOresult = 2;
    } 

    first = std::sqrt((b2.x - a1.x) * (b2.x - a1.x) + (b2.y - a1.y) * (b2.y - a1.y)); 
    second = std::sqrt((b2.x - b1.x) * (b2.x - b1.x) + (b2.y - b1.y) * (b2.y - b1.y));

    if (std::abs(first + second - result) < 1e-8) {
       //std::cout << "YES"; 
       TOresult = 2;
    } 

    //std::cout << "NO";

    return TOresult;
}

int main() {
    long long N; 
    Point A; 
    Point B(10047,10025);

    std::cin >> N >> A;
    std::vector <Point> array;
    for (size_t i = 0; i < N; ++i) {
        Point buf;
        std::cin >> buf;
        array.push_back(buf);
    }
    array.push_back(array[0]);
    int count = 0; 
    for (size_t i = 0; i < N; ++i) {
       // std::cout << array[i].x << " " << array[i].y  << "\n";
       int res = solve(A,B,array[i],array[i+1]);
        if (res == 0) {
            continue;
        }
        if (res == 1) {
            ++count;
            continue;
        }
        if (res == 2) {
            std::cout << "YES";
            return 0;
        }
        //std::cout << solve(A,B,array[i],array[i+1]) << "\n";
    }
    //std::cout << count;
    if (count % 2 == 1) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}
