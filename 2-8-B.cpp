#include <iostream>
#include <vector>
#include <string>

struct DFS {
    std::vector<std::vector<long long>> node_edges;
    std::vector <std::string> nodes_color;
    std::vector<long long> time_in;
    std::vector<long long> time_out;
    long long time;

    DFS(long long n) {
        for (long long i = 0; i < n + 1; ++i) {
            node_edges.push_back(std::vector<long long>());
            nodes_color.push_back("WHITE");
            time_in.push_back(0);
            time_out.push_back(0);
        }
        time = 0;
    }

    void do_DFS(long long number) {
        time_in[number] = time++;
        nodes_color[number] = "GREY";
        for (long long i = 0; i < node_edges[number].size(); ++i) {
            if (nodes_color[node_edges[number][i]] != "WHITE") {
                continue;
            }
            else {
                do_DFS(node_edges[number][i]);
            }
        }
        nodes_color[number] = "BLACK";
        time_out[number] = time++;
    }

    bool answer(long long n_1, long long n_2) {
        return (time_in[n_1] < time_in[n_2] && time_out[n_1] > time_out[n_2]);
    }


};

int main() {
    long long n;
    std::cin >> n;
    DFS graph(n);
    long long root;
    for (long long i = 1; i < n + 1; ++i) {
        long long prev;
        std::cin >> prev;
        if (prev == 0) {
            root = i;
        } else {
            graph.node_edges[prev].push_back(i);
        }
    }
    /*
    for (long long i = 1; i < n + 1; ++i) {
        std::cout << i << " : ";
       for (long long j = 0; j < graph.node_edges[i].size(); ++j) {
           std::cout << graph.node_edges[i][j] << " ";
       }
       std::cout << '\n';
    }
    */

    graph.do_DFS(root);
    long long num;
    std::cin >> num;
    for (int i = 0; i < num; ++i) {
        long long x;
        long long y;
        long long ans;
        std::cin >> x >> y;
        ans = graph.answer(x,y);
        std::cout << ans << '\n';
    }
    return 0;
}
