#include <iostream>
#include <vector>
#include <map>
#include <set>




typedef  long long ll;
int main() {
    ll INF = 10e8;
    std::vector<std::vector<std::pair<ll, ll>>> graph;
    std::set <std::pair<ll, ll>> distancec;
    std::vector<ll> v_distancec;
    //std::map <ll,ll> distance;
    std::vector<ll> answer;

    ll number_nodes;
    ll number_edges;
    std::cin >> number_nodes >> number_edges;

    ll begin;
    ll end;
    std::cin >> begin >> end;

    for (ll i = 0; i < number_nodes + 1; ++i ) {
        graph.push_back(std::vector<std::pair<ll, ll>>());
        answer.push_back(INF);
        v_distancec.push_back(INF);
    }

    for (ll i = 1; i < number_nodes + 1; ++i) {
        if (i == begin) {
            //distance[i] = 0; // map
            distancec.insert(std::make_pair(0,i)); // set
            v_distancec[i] = 0;
        }
        else {
           // distance[i] = INF; // map
            distancec.insert(std::make_pair(INF,i)); //set
        }
    }
    ll x;
    ll y;
    ll dist;

    for (ll i = 0; i < number_edges; ++i) {
        std::cin >> x >> y >> dist;
        graph[x].push_back(std::make_pair(y,dist));
        graph[y].push_back(std::make_pair(x,dist));
    }

    while (!distancec.empty()) {
        auto it = distancec.begin();
        ll node_from = (*it).second;
        ll node_delta = (*it).first;
        ll node_to = 0;
        distancec.erase(it);
        for (int i = 0; i < graph[node_from].size(); ++i) {
            node_to = graph[node_from][i].first;
            auto it_to = distancec.find(std::make_pair(v_distancec[node_to],node_to));
            if (it_to != distancec.end()) {;
                if ( it_to->first > node_delta + graph[node_from][i].second ) {
                    ll save = it_to->second;
                    distancec.erase(it_to);
                    distancec.insert(std::make_pair(node_delta + graph[node_from][i].second, save));
                    v_distancec[save] = graph[node_from][i].second + node_delta;
                }
            }
        }
        answer[node_from] = node_delta;
    }

    if (answer[end] == INF) {
        std::cout << -1;
    }
    else {
    std::cout << answer[end];
    }

    return 0;
}
