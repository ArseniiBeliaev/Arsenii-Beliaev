#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
struct Point {
    long long x;
    long long y;
    Point(): x(0),y(0){}
    Point(long long x, long long y):x(x),y(y){}
    friend std::istream& operator>> (std::istream &in, Point &point);
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
};

std::ostream& operator<< (std::ostream &out, const Point &point)
{
    out << point.x << " " << point.y;
    return out;
}

std::istream& operator>> (std::istream &in, Point &point)
{
    in >> point.x;
    in >> point.y;
    return in;
}

long double length(const Point& first,const Point& second) {
    return sqrt((first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y));
}

std::vector <Point> points;

struct Vector 
{
    Point great; 
    Vector(){}
    Vector (Point x, Point y) {
        great.x = -x.x + y.x;
        great.y = -x.y + y.y;
    }
};

long long vector_comp(const Vector& first, const Vector& second) {
    return first.great.x * second.great.y - first.great.y * second.great.x;
}

bool comp(const Point &p1, const Point &p2) {
    long long int temp = vector_comp(Vector(points[0], p1),Vector(p1,p2));
    if (fabs(temp) < 1e-6) {
        return length(points[0], p1) < length(points[0], p2);
    }
    else {
        return temp < 0;
    }
}

std::vector<Point> graham_scan(int n) {
    std::vector<Point> C;
    int top = 1;
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].x < points[index].x || (points[i].x == points[index].x
                                              && points[i].y < points[index].y)) {
            index = i;
        }
    }
    std::swap(points[0], points[index]);
    C.push_back(points[0]);
    std::sort(points.begin() + 1, points.end(), comp);
    C.push_back(points[1]);

    for (int i = 2; i < n; ++i) {
        while (top > 0 && vector_comp(Vector(C[top - 1], C[top]),Vector(C[top],points[i])) >= 0) {
            --top;
            C.pop_back();
        }
        C.push_back(points[i]);
        ++top;
    }
    return C;
}

int main() {
    int N;
    std::cin >> N;
    Point x;
    for (size_t i = 0; i < N; i++) {
        std::cin >> x; 
        points.push_back(x);
    }
    std::vector <Point> answer = graham_scan(N);
    std::cout << answer.size() << "\n";
    for (size_t i = 0; i < answer.size(); ++i){
        std::cout << answer[i] << "\n";
    }
}
