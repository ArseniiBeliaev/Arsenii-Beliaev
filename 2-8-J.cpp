#include <iostream>
#include <vector>
#include <string>
#include <stack>



struct DFS {
    std::vector<std::vector<long long>> node_edges;
    std::vector<std::pair <long long, long long>> ans;

    DFS(long long n) {
        for (long long i = 0; i < n; ++i) {
            node_edges.push_back(std::vector<long long>());
        }
    }

    void DoDFS(long long number, int prev ) {
        while(!node_edges[number].empty()) {
            long long save = node_edges[number][node_edges[number].size() - 1];
            node_edges[number].pop_back();
            DoDFS(save,number);
        }

        if (prev != - 1) {
            ans.push_back(std::make_pair(prev+1,number+1));
        }
    }
};

int main() {
    long long a;
    long long n;
    std::cin >> n >> a;
    DFS graph(n);
    int x  = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> x;
            x = !x;
            if ( i != j  && x == 1) {
                graph.node_edges[i].push_back(j);
                //graph.node_edges[j].push_back(i);
                //std::cout << "fe";
            }
        }
    }

    graph.DoDFS(a-1,-1);
    for (int i = graph.ans.size() - 1; i > -1 ; --i) {
        std::cout << graph.ans[i].first << ' ' << graph.ans[i].second << '\n';
    }
    return 0;
}
