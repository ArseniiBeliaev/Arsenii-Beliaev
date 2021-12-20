#include <iostream>
#include <vector>
#include <map>
#include <string>
 
class Bor {
  static const int alphabet = 26;
  struct node {
    int to[alphabet];
    int term;
    node() {
      for (int i = 0; i < alphabet; ++i) {
        to[i] = -1;
      }
      term = 0;
    }
  };
  std::vector<node> trie;
 
 public:
  Bor() {
    trie.push_back(node());
  }
 
  void add(const std::string &s) {
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
      if (trie[v].to[s[i] - 'a'] == -1) {
        trie.push_back(node());
        trie[v].to[s[i] - 'a'] = trie.size() - 1;
      }
      v = trie[v].to[s[i] - 'a'];
    }
    ++trie[v].term;
  }
 
  void dfs(int v, std::vector<std::string> &sorted, std::string &s) {
    for (int i = 0; i < alphabet; ++i) {
      if (trie[v].to[i] != -1) {
        s += char('a' + i);
        if (trie[trie[v].to[i]].term > 0) {
          for (int j = 0; j < trie[trie[v].to[i]].term; ++j) {
            sorted.push_back(s);
          }
        }
        dfs(trie[v].to[i], sorted, s);
        s.pop_back();
      }
    }
  }
  std::vector<std::string> sort(const std::vector<std::string> &dict) {
    for (const auto &i : dict) {
      add(i);
    }
    std::vector<std::string> sorted;
    std::string s = "";
    dfs(0, sorted, s);
    return sorted;
  }
};
 
int main() {
  std::string s;
  std::cin >> s;
  std::vector<int> str;
  std::vector<std::string> dict;
  std::string t = "";
  for (size_t i = 0; i < s.size(); ++i) {
    if (i == 0) {
      str.push_back(0);
      if (s[i] == '.') {
        ++str[str.size() - 1];
      } else {
        t += s[i];
      }
    } else {
      if (s[i] == '.') {
        if (s[i - 1] != '.') {
          str.push_back(0);
          if (t != "") {
            dict.push_back(t);
            t = "";
          }
        }
        ++str[str.size() - 1];
      } else {
        str.push_back(0);
        t += s[i];
      }
    }
  }
  if (t != "") {
    dict.push_back(t);
  }
  Bor bor;
  std::vector<std::string> sorted = bor.sort(dict);
  std::string ans = "";
  int count = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '.') {
      ans += '.';
    } else {
      if (i == 0 || s[i - 1] == '.') {
        ans += sorted[count];
        ++count;
      }
    }
  }
  std::cout << ans;
  return 0;
}
