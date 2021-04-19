#include <iostream>
#include <string>
#include <vector>



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string str1;
    std::string str2;
    std::cin >> str1 >> str2;
    str1 = "0" + str1;
    str2 = "0" + str2;
    std::string answer;
    short dp_f[str2.size()];
    short  dp_s[str2.size()];
    for (int j = 0; j < str2.size(); ++j) {
        dp_f[j] = 0;
        dp_s[j] = 0;
    }
    //bool dp_rec[str1.size()][str2.size()];
    std::vector <std::vector <bool>> dp_rec;
    for (int i = 0; i < str1.size(); ++i) {
        std::vector <bool> nw;
        dp_rec.push_back(nw);
        for (int j = 0; j < str2.size(); ++j) {
            dp_rec[i].push_back(false);
        }
    }

    for (int i = 1; i < str1.size(); ++i) {
        for (int j = 1; j < str2.size(); ++j) {
            if (i % 2 == 1) { // dp_s = i - 1 || dp_f = i
                if (str1[i] == str2[j]) {
                    dp_f[j] = dp_s[j - 1] + 1;
                    dp_rec[i][j] = true; // -1 -1
                } else {
                    if (dp_s[j] > dp_f[j - 1]) {
                        dp_f[j] = dp_s[j];
                        dp_rec[i][j] = true; // -1 0
                    } else {
                        dp_f[j] = dp_f[j - 1];
                        dp_rec[i][j] = false; // 0 -1
                    }
                }
            }
            else { // dp_s = i || dp_f = i-1
                if (str1[i] == str2[j]) {
                    dp_s[j] = dp_f[j - 1] + 1;
                    dp_rec[i][j] = true;
                } else {
                    if (dp_f[j] > dp_s[j - 1]) {
                        dp_s[j] = dp_f[j];
                        dp_rec[i][j] = true;
                    } else {
                        dp_s[j] = dp_s[j - 1];
                        dp_rec[i][j] = false;
                    }
                }
            }
        }
    }

    int i = str1.size() - 1;
    int j = str2.size() - 1;
    do {
        int ci = i;
        int cj = j;
        if ( str1[i] == str2[j]) {
            answer.push_back(str1[i]);
            i = i - 1;
            j = j - 1;
            continue;
        }
        if (dp_rec[ci][cj]) {
            i = i - 1;
            continue;
        }
        else if (!dp_rec[ci][cj]) {
            j = j - 1;
            continue;
        }
    } while ( i > 0 && j > 0);
    for (int i = answer.size() - 1; i > -1; --i) {
        std::cout << answer[i];
    }
    return 0;
}
