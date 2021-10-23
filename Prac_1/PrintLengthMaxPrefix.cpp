#include <iostream>
#include <map>
#include <set> 
#include <vector>
#include <stack>
#include <string>
#include "PrintLengthMaxPrefix.h"

    
Graph::Graph(const std::string& symbol) {
        // Создание начальной вершины 
        nodes.push_back(Node());
        // Создание новой веришны, теперь она термальная 
        nodes.push_back(Node());
        term_nodes.push_back(1);
        nodes[1].term = true;
        // Создание symbol-перехода в новую вершину 
        nodes[0].edges.push_back(std::make_pair(1,symbol));
        // Кажись граф созданькали 
    } 
// Объединение : Merge 
void Graph::Merge(const Graph& another) {
        // Сдвиг 
        int shift = nodes.size();
        // Создание Epsilon-перехода в начальную вершину другой строки
        nodes[0].edges.push_back(std::make_pair(shift, std::string("E"))); 
        for (size_t i = 0; i < another.nodes.size(); ++i) {
            nodes.push_back(another.nodes[i]);
            // Если вершина была термальной, то теперь она будет теремальной 
            // И после merge  
            if (another.nodes[i].term) {term_nodes.push_back(shift + i);} 
            // Сдвинем вершины в которые мы переходим на shift, т/е на размер 
            // массива к которому добавляем
            for(size_t j = 0; j < nodes[shift + i].edges.size(); ++j) {
                nodes[shift + i].edges[j].first += shift; 
            }
        }
    }
// Замыкание 
void Graph::Closure() {
        // Из каждой термальной вершины создадим Epsilon-переход в начальную 
        for (size_t i = 0; i < term_nodes.size(); ++i) {
            // Проверка "есть ли у нас уже Epcilon-переход в начальную вершину"
            bool check = true;
            for (size_t j = 0; j < nodes[term_nodes[i]].edges.size(); ++j) {
                if (nodes[term_nodes[i]].edges[j] == std::make_pair(0,std::string("E"))) {check = false;}
            }
            // Если Epsilon-перехода не было, то создать его 
            if (check) { nodes[term_nodes[i]].edges.push_back(std::make_pair(0, std::string("E"))); }
        }
        for (size_t i = 0; i < term_nodes.size(); ++i) {
            nodes[term_nodes[i]].term = false;
        }
        term_nodes.clear();
        term_nodes.push_back(0);
        nodes[0].term = true;
    }
// Конкатенация  
void Graph::Concatenation (const Graph& another) {
        // К каждому завершающему состоянию мы добавим граф another
        // и старые завершающие состояния заменим на новые 
        size_t term_nodes_size = term_nodes.size();
        std::vector <int> new_term_nodes; 
        for (size_t i = 0; i < term_nodes_size; ++i) {
           size_t shift = nodes.size();
            for (size_t j = 0; j < another.nodes.size(); ++j) {
                nodes.push_back(another.nodes[j]);
                if (another.nodes[j].term) {new_term_nodes.push_back(shift + j);}
                for (size_t p = 0; p < nodes[shift + j].edges.size(); ++p) {
                    nodes[shift + j].edges[p].first += shift; 
                }
            }
            nodes[term_nodes[i]].edges.push_back(std::make_pair(shift, std::string("E")));
        }
        // Обнуление у самих бывших "термальных" вершин 
        for (size_t i = 0; i < term_nodes.size(); ++i) {
            nodes[term_nodes[i]].term = false;
        }

        term_nodes = new_term_nodes;
    }
/*
    void print() {
        std::cout << "Graph" << '\n'; 
        for (int i = 0; i < nodes.size(); ++i) {
            std::cout << '\n'; 
            for (int j = 0; j < nodes[i].edges.size(); ++j) {
                std::cout << i << "-" << nodes[i].edges[j].second << "-" << nodes[i].edges[j].first; 
                std::cout << '\n';
            }
            if (nodes[i].term) {
                std::cout << i << " - TERMINAL" << '\n';
            }
            else {
                std::cout << "NoTerminal" << '\n';
            }
        }

        std::cout << "TERMINALs" << '\n';
        for (int i = 0; i < term_nodes.size(); ++i) {
            std::cout << term_nodes[i] << ' ';
        }
    }
   */
bool Graph::Search(std::string& world) const {
        if (world.size()==0) {return nodes[0].term;}
        std::set <std::pair<size_t,size_t> > check;
        check.insert(std::make_pair(0,0));
        // .first - номер вершины 
        // .second - номер буквы в world 
        std::deque <std::pair<size_t,size_t> > dfs_tree;
        dfs_tree.push_back(std::make_pair(0,0));
        while(!dfs_tree.empty()) {
            size_t open_node =  dfs_tree.front().first;
            size_t number_symbol = dfs_tree.front().second;

            const Node& openned = nodes[open_node];
            std::string symbol;
            symbol.push_back(world[number_symbol]);
            //std::cout << symbol;

            for (size_t i = 0; i < openned.edges.size(); ++i) {
                // Обработка обычного перехода 
                if(openned.edges[i].second == symbol) {
                    size_t node_to = openned.edges[i].first;
                    if (number_symbol == (world.size()-1)) {
                        // return true, если:
                        // 1) Вершина сама термальная 
                        // 2) из нее есть Epsilon переходы в термальные 
                        if (nodes[node_to].term) return true;
                        if (check.find(std::make_pair(node_to,number_symbol)) == check.end()) {
                            dfs_tree.push_back(std::make_pair(node_to,number_symbol + 1));
                            check.insert(std::make_pair(node_to,number_symbol + 1));
                            //std::cout << node_to << ' ' << number_symbol << '\n';
                        }
                        //std::cout << node_to << ' ' << number_symbol << '\n';
                    }
                    else {
                        size_t new_number_symbol = number_symbol + 1;
                        if (check.find(std::make_pair(node_to,new_number_symbol)) == check.end()) {
                            dfs_tree.push_back(std::make_pair(node_to,new_number_symbol));
                            check.insert(std::make_pair(node_to,new_number_symbol));
                            //std::cout << node_to << ' ' << new_number_symbol << '\n';
                        }
                        //std::cout << node_to << ' ' << new_number_symbol << '\n';
                    }
                }
                // Обработка Epsilon перехода 
                if (openned.edges[i].second == "E") {
                    size_t node_to = openned.edges[i].first;
                    if (nodes[node_to].term && number_symbol>(world.size()-1)) return true;
                    if (check.find(std::make_pair(node_to,number_symbol)) == check.end()) {
                        dfs_tree.push_back(std::make_pair(node_to,number_symbol));
                        check.insert(std::make_pair(node_to,number_symbol));
                        //std::cout << node_to << ' ' << number_symbol << '\n';
                    }
                    //std::cout << node_to << ' ' << number_symbol << '\n';
                }
            }
            //std::cout << dfs_tree.size() << '\n'; 
            dfs_tree.pop_front();
        }
        return false;
    }

Graph Created(const std::string& str) {
    std::stack <Graph> automats;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != '*' && str[i] != '+' && str[i] != '.') {
            std::string s;
            s.push_back(str[i]);
            automats.push(Graph(s));
        }

        else {
            if (str[i] == '*') {
                // Обработка неправильной польской записи 
                if (automats.size() < 1) {
                    throw("Error. No correct operation *");
                }
                Graph copy = automats.top(); 
                copy.Closure(); 
                automats.pop();
                automats.push(copy); 
            }

            if (str[i] == '+') {
                if (automats.size() < 2) {
                    throw("Error. No correct operation +");
                }
                Graph copy1 = automats.top();
                automats.pop();
                Graph copy2 = automats.top();
                automats.pop();
                copy1.Merge(copy2);
                automats.push(copy1);
            }

            if (str[i] == '.') {
                if (automats.size() < 2) {
                    throw("Error. No correct operation .");
                }
                Graph copy1 = automats.top();
                automats.pop();
                Graph copy2 = automats.top();
                automats.pop();
                copy2.Concatenation(copy1);
                automats.push(copy2);
            }
        } 
    }
    if (automats.size() != 1) {
        throw("Error. No correct number of operations and symbols");
    }
    return automats.top();
}

int FindMaxPrefix(std::string prefix,const Graph& graph) {
    while(prefix.size()) {
        if(graph.Search(prefix)) {return prefix.size();}
        prefix.erase(prefix.end()-1);
    }
    return 0;
}

int PrintLengthMaxPrefixX() {
    std::string prefix; 
    std::string regular_str; 
    std::cin >> regular_str >> prefix;
    Graph regular_str_graph = Created(regular_str); 
    return FindMaxPrefix(prefix,regular_str_graph);
}

int PrintLengthMaxPrefixX(std::string regular_str, std::string prefix) {
        Graph regular_str_graph = Created(regular_str); 
        return FindMaxPrefix(prefix,regular_str_graph);
}
