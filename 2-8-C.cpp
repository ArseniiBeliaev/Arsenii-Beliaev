#include <iostream>
#include <vector>
#include <string>
#include <stack>

enum Color { White, Grey, Black };

struct DFS {
    std::vector<Color> nodes_color;

    std::vector<std::vector<long long>> node_edges;
    long long start_loop_vertex = 0;

    std::vector<long long> ans;

    DFS(long long n) {
        for (long long i = 0; i < n; ++i) {
            node_edges.push_back(std::vector<long long>());
            nodes_color.push_back(White);
        }
    }

    void DoDFS(long long number) {
        nodes_color[number] = Grey;
        ans.push_back(number);

        for (long long i = 0; i < node_edges[number].size(); ++i) {
            if (nodes_color[node_edges[number][i]] == Grey) {
                start_loop_vertex = node_edges[number][i];
                throw 1;
            } else if (nodes_color[node_edges[number][i]] == White){
                DoDFS(node_edges[number][i]);
            }
        }

        ans.pop_back();
        nodes_color[number] = Black;
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

    try {
        for (long long i = 0; i < graph.nodes_color.size() ; ++i) {
            if (graph.nodes_color[i] == White) {
                graph.DoDFS(i);
            }
        }
    } catch(...) {

    }

    if (!graph.ans.empty()) {
        std::cout << "YES\n";

        long long i = 0;

        for (; i < graph.ans.size(); ++i) {
            if (graph.ans[i] == graph.start_loop_vertex) {
                break;
            }
        }

        for (; i < graph.ans.size(); ++i) {
            std::cout << (graph.ans[i] + 1) << ' ';
        }
    } else {
        std::cout << "NO";
    }

    return 0;
}
