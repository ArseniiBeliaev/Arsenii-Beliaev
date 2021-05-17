#include <iostream>
#include <vector>
#include <deque>
void print(std::pair<int, int> other) {
    std::cout << "(" << other.first << "," << other.second << ") ";
}
char fix(int x) {
    switch (x) {
        case 1:
            return 'a';
        case 2:
            return 'b';
        case 3:
            return 'c';
        case 4:
            return 'd';
        case 5:
            return 'e';
        case 6:
            return 'f';
        case 7:
            return 'g';
        case 8:
            return 'h';
    }
    return 'j';
}
int fix(char x) {
    switch (x) {
        case 'a':
            return 1;
        case 'b':
            return 2;
        case 'c':
            return 3;
        case 'd':
            return 4;
        case 'e':
            return 5;
        case 'f':
            return 6;
        case 'g':
            return 7;
        case 'h':
            return 8;
    }
    return 9;
}
bool check(int x, int y) {
    return (x > 0 && y > 0 && x < 9 && y < 9);
}
int main() {
    // ВВОД
    std::pair <int, int> begin, end;
    char x;
    int int_x;
    int y;
    std::cin >> x >> y;
    int_x = fix(x);
    end = std::make_pair(int_x,y);
    std::cin >> x >> y;
    int_x = fix(x);
    begin = std::make_pair(int_x,y);
    // Реализация БФS
    std::pair<int, int> null = std::make_pair(0,0);
    std::vector<std::vector<std::pair<int, int>>> desk;
    std::deque<std::pair<int, int>> deq;
    for (int i = 0; i < 9; ++i) {
        desk.push_back(std::vector<std::pair<int,int>>(9,null));
    }

    desk[begin.first][begin.second] = begin;
    int var_x = begin.first;
    int var_y = begin.second;
    deq.push_back(begin);
    while (std::make_pair(var_x,var_y) != end) {
        var_x = deq.front().first;
        var_y = deq.front().second;
        deq.pop_front();
        if (check(var_x+1,var_y+2))
        {
            if (desk[var_x+1][var_y+2] == null)
            {
                desk[var_x + 1][var_y + 2] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x + 1, var_y + 2));
            }
        }
        if (check(var_x+2,var_y+1))
        {
            if (desk[var_x+2][var_y+1] == null) {
                desk[var_x + 2][var_y + 1] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x + 2, var_y + 1));
            }
        }
        if (check(var_x-1,var_y+2))
        {
            if (desk[var_x-1][var_y+2] == null) {
                desk[var_x - 1][var_y + 2] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x - 1, var_y + 2));
            }
        }
        if (check(var_x+1,var_y-2) )
        {
            if (desk[var_x+1][var_y-2] == null) {
                desk[var_x + 1][var_y - 2] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x + 1, var_y - 2));
            }
        }
        if (check(var_x-2,var_y+1))
        {
            if (desk[var_x-2][var_y+1] == null) {
                desk[var_x - 2][var_y + 1] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x - 2, var_y + 1));
            }
        }
        if (check(var_x+2,var_y-1))
        {
            if (desk[var_x+2][var_y-1] == null) {
                desk[var_x + 2][var_y - 1] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x + 2, var_y - 1));
            }
        }
        if (check(var_x-1,var_y-2) )
        {
            if (desk[var_x-1][var_y-2] == null) {
                desk[var_x - 1][var_y - 2] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x - 1, var_y - 2));
            }
        }
        if (check(var_x-2,var_y-1))
        {
            if (desk[var_x-2][var_y-1] == null) {
                desk[var_x - 2][var_y - 1] = std::make_pair(var_x, var_y);
                deq.push_back(std::make_pair(var_x - 2, var_y - 1));
            }
        }
    }

    std::pair<int, int> buffer;
    buffer = end;
    while (buffer != begin) {
        std::cout << fix(buffer.first) << buffer.second << '\n';
        buffer = desk[buffer.first][buffer.second];
    }
    std::cout << fix(buffer.first) << buffer.second << '\n';
    return 0;
}
