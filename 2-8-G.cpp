#include <iostream>
#include <vector>
#include <string>
#include <stack>

enum Color { White, Black };

struct DFS {
    std::vector<Color> nodes_color;
    std::vector<std::vector<long long>> node_edges;
    std::vector<long long> ans;
    long long max = 0;
    long long comp = 1;

    DFS(long long n) {
        for (long long i = 0; i < n; ++i) {
            node_edges.push_back(std::vector<long long>());
            nodes_color.push_back(White);
            ans.push_back(0);
        }
        comp = 1;
    }

    void wrapDFS() {
        for (long long j = 0; j < node_edges.size(); ++j) {
            if (nodes_color[j] == White) {
                DoDFS(j);
                comp++;
            }
        }
    }

    void DoDFS(long long number) {
        nodes_color[number] = Black;
        ans[number] = comp;
        for (long long i = 0; i < node_edges[number].size(); ++i) {
             if ( nodes_color[node_edges[number][i]] == White ) {
                DoDFS(node_edges[number][i]);
            }
        }
    }
};

int main() {


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
        graph.node_edges[y].push_back(x);
    }

    graph.wrapDFS();
    std::cout << graph.comp << '\n';
    for (long long i  = 0; i < graph.ans.size(); ++i) {
        std::cout << graph.ans[i] << ' ';
    }

    return 0;
}
