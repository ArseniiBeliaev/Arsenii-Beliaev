#include <iostream>

//Nani? Это что за дезинтыгратор кодстайлов. Как же блин... ладно
int main() {
    int INF = 1e9;// Маловат будет. Для этого есть системные константы, по типу INT_MAX
    int num;
    std::cin >> num;

    int graph[num][num];
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < num; ++j) {
            std::cin >> graph[i][j];
        }
    }

    std::pair <int, int> dp[num][(1 << num)];
    for (int i = 0; i < num; ++i) {
        for (int j = 0; j < (1 << num); ++j) {
            dp[i][j].first = INF;
            dp[i][1 << i].first = 0;
        }
    }

    for (unsigned int mask = 1; mask < (1 << num); ++mask) {
        for (unsigned int node_v = 0; node_v < num; ++node_v) {
            if ((mask >> node_v) & 1) {
                for (int node_u = 0; node_u < num; ++node_u) {
                    if ((mask >> node_u) & 1) continue;
                    int new_mask = (mask | (1 << node_u));
                    dp[node_u][new_mask].first = std::min(dp[node_u][new_mask].first, dp[node_v][mask].first + graph[node_u][node_v]);
                    if (dp[node_u][new_mask].first == (dp[node_v][mask].first + graph[node_u][node_v])) {
                        dp[node_u][new_mask].second = node_v;
                    }
                }
            }
        }
    }

    int min = INF;
    int min_node = 0;
    //std::cout << dp[1][1 << 1];

    for (int node = 0; node < num; ++node ) {
        if (min > dp[node][(1 << num) - 1].first) {
            min = dp[node][(1 << num) - 1].first;
            min_node = node;
        }
    }

    std::cout << min << '\n';
    int mask = (1 << num) - 1;
    std::cout << min_node + 1 << " ";
    
    for (int i = 0; i < num-1; ++i) {
        int prev = dp[min_node][mask].second;
        std::cout << prev + 1 << " ";
        mask = mask ^ (1 << min_node);
        min_node = prev;
    }
    
    return 0;
}

