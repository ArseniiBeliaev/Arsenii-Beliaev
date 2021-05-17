#include <iostream>
#include <vector>

typedef long long ll;
struct Edge {
    int from;
    int to;
    ll dist;
    Edge(int from, int to, ll dist):from(from), to(to), dist(dist) {}
};

void DFS (int Node, std::vector<Edge>& data, std::vector<bool>& check_dfs) {
    check_dfs[Node] = true;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].from == Node && !check_dfs[data[i].to]) {
            DFS(data[i].to, data, check_dfs);
        }
    }
}

int main() {
    std::vector<bool> check_dfs;
    std::vector<int> bad_nodes;
    ll INF = 10e17;
    int number_nodes;
    int number_edges;
    int begin;
    std::cin >> number_nodes >> number_edges >> begin;
    begin--;
    std::vector<Edge> data;
    for (int i = 0; i < number_edges; ++i) {
        int x;
        int y;
        ll dist;
        std::cin >> x >> y >> dist;
        Edge e(x-1,y-1,dist);
        data.push_back(e);
    }

    std::vector<ll> answer;
    for (int i = 0; i < number_nodes; ++i) {
        answer.push_back(INF);
        if (i == begin) {
            answer[i] = 0;
        }
        check_dfs.push_back(false);
    }

    for (int i = 0; i < number_nodes + 1; ++i) {
        for (int j = 0; j < number_edges; ++j ) {
            if (answer[data[j].from] < INF) {
                if (answer[data[j].to] > answer[data[j].from] + data[j].dist ) {
                    answer[data[j].to] = answer[data[j].from] + data[j].dist;
                    if (i == number_nodes) {
                        bad_nodes.push_back(data[j].to);
                    }
                }
            }
        }
    }
    /*
    for (int i = 0; i < bad_nodes.size(); ++i) {
        std::cout << bad_nodes[i] << " ";
    }
    */
    for (int i = 0; i < bad_nodes.size(); ++i) {
        if (!check_dfs[bad_nodes[i]]) {
            DFS(bad_nodes[i],data,check_dfs);
        }
    }

    for (int i = 0; i < number_nodes; ++i) {

        if (answer[i] == INF) {

            std::cout << "*\n";

            continue;
        }

        if (check_dfs[i]) {
            std::cout << "-" << "\n";
            continue;
        }

        std::cout << answer[i] << '\n';
    }
    return 0;
}
