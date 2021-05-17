#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <set>

enum Color { White, Grey, Black };
struct DFS {
    std::set<std::pair<long long, long long>> bridgs;
    std::vector <Color> nodes_colors;
    std::vector <std::vector<long long>> node_edges;
    std::vector<std::pair<long long, long long>> edges;
    long long answer_edges;
    std::vector<long long> tin;
    long long time;
    std::vector <long long> ret;

    DFS(long long n) {
        for (long long i = 0; i < n; ++i) {
            node_edges.push_back(std::vector<long long>());
            nodes_colors.push_back(White);
            //edges.push_back(std::make_pair(0,0));
            tin.push_back(0);
            ret.push_back(0);
        }
        time = 0;
        answer_edges = 0;
    }

    void DoDFS(long long node, long long par) {
        tin[node] = time++;
        ret[node] = tin[node];
        nodes_colors[node] = Grey;
        for (long long i  = 0; i < node_edges[node].size(); ++i) {
            if (node_edges[node][i] == par) {
                continue;
            }

            if (nodes_colors[node_edges[node][i]] == Grey) {
                ret[node] = std::min(ret[node], tin[node_edges[node][i]]);
            }

            else {
                DoDFS(node_edges[node][i],node);
                if (ret[node_edges[node][i]] == tin[node_edges[node][i]]) {
                    answer_edges++;
                    std::pair <long long, long long> bridgess = std::make_pair(node,node_edges[node][i]);
                    std::pair <long long, long long> bridgess_2 = std::make_pair(node_edges[node][i],node);
                    bridgs.insert(bridgess_2);
                    bridgs.insert(bridgess);
                }
            }
            ret[node] = std::min(ret[node], ret[node_edges[node][i]]);
        }
    }


};

int main() {
    long long v;
    long long m;
    std::cin >> v;
    std::cin >> m;
    DFS graph(v);
    long long x = 0;
    long long y = 0;
    for (long long i = 0; i < m; ++i) {
        std::cin >> x >> y;
        x--;
        y--;
        graph.node_edges[x].push_back(y);
        graph.node_edges[y].push_back(x);
        graph.edges.push_back(std::make_pair(x,y));

    }
    graph.DoDFS(x,-1);
    std::cout << graph.answer_edges << '\n';
    for (long long i = 0; i < graph.edges.size(); ++i) {
        if (graph.bridgs.find(graph.edges[i]) != graph.bridgs.end()) {
            std::cout << i + 1 << '\n';
        }
    }
    return 0;
}
