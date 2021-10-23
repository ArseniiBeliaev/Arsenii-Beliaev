#include <iostream>
#include <map>
#include <set> 
#include <vector>
#include <stack>
#include <string>

struct Node
{
    bool term = false;
    std::vector <std::pair<int, std::string> > edges;
};

struct Graph
{
    std::vector <Node> nodes; 
    std::vector <int> term_nodes; 
    Graph(const std::string& symbol);
    void Merge(const Graph& another);
    void Closure();
    void Concatenation(const Graph& another);
    bool Search(std::string& world) const; 
};

Graph Created(const std::string& str); 
int FindLengthMaxPrefix(std::string str,const Graph& graph);
int  PrintLengthMaxPrefixX();
int  PrintLengthMaxPrefixX(std::string regular_str, std::string prefix);