#include <iostream>
#include <vector>
#include <string>
#include <stack>

enum Color { White, Grey, Black };

struct DFS {
    std::vector<Color> nodes_color;
    std::vector<std::vector<long long>> node_edges;
    std::vector<long long> ans;


    DFS(long long n) {
        for (long long i = 0; i < n; ++i) {
            node_edges.push_back(std::vector<long long>());
            nodes_color.push_back(White);
        }
    }

    void check(long long number) {
        nodes_color[number] = Grey;
        for (long long i = 0; i < node_edges[number].size(); ++i) {
            if (nodes_color[node_edges[number][i]] == Grey) {
                throw 1;
            } else if (nodes_color[node_edges[number][i]] == White){
                check(node_edges[number][i]);
            }
        }
        nodes_color[number] = Black;
    }

    void fix() {
        for (int i = 0; i < nodes_color.size(); ++i) {
            nodes_color[i] = White;
        }
    }



    void wrpDoDFS() {
        for (long long i = 0; i < node_edges.size(); ++i) {
            if (nodes_color[i] == White) {
                DoDFS(i);
            }
        }
    }

    void DoDFS(long long number) {
        nodes_color[number] = Grey;
        for (long long i = 0; i < node_edges[number].size(); ++i) {
            if (nodes_color[node_edges[number][i]] == Grey) {
                throw 1;
            }
            if (nodes_color[node_edges[number][i]] == White) {
                DoDFS(node_edges[number][i]);
            }
        }
        nodes_color[number] = Black;
        ans.push_back(number);
    }


};

int main() {
    std::ios_base::sync_with_stdio(false);

    long long v;
    long long r;
    std::cin >> v >> r;
    DFS graph(v);

    int x = 0;
    int y = 0;
    for (long long i = 0; i < r; ++i) {
        std::cin >> x >> y;
        --x; --y;
        graph.node_edges[x].push_back(y);
    }

    int che = 1;
    try {
        for (long long i = 0; i < graph.nodes_color.size() ; ++i) {
            if (graph.nodes_color[i] == White) {
                graph.check(i);
            }
        }
    } catch(...) {
        std::cout << -1;
        che = 0;
    }
    if (che) {
        try {
            graph.fix();
            graph.wrpDoDFS();
        } catch (...) {
            std::cout << -1;
        }
        for (int i = graph.ans.size() - 1; i > -1; --i) {
            std::cout << graph.ans[i] + 1 << ' ';
        }
    }
    return 0;
}
