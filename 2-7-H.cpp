#include <iostream>






int main() {
  long long n;
  long long m;
  std::cin >> n >> m;
  long long mask_max = (1 << n);
  //std::cout << mask_max;
  long long dp[mask_max][m];

  for (long long i = 0; i < mask_max; ++i) {
    for (long long j = 0; j < m; ++j) {
      dp[i][j] = 0;
    }
  }

  long long check_1[m];
  long long check_2[m];
  for (long long i = 0; i < m; ++i) {
    check_1[i] = 0;
    check_2[i] = 0;
  }


  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < m; ++j) {
      char a;
      std::cin >> a;
      if (a == '+') {
        check_1[j] += (1 << (n-i-1));
        check_2[j] += (1 << (n-i-1));
      }
      if (a == '.') {
        check_1[j] += (1 << (n-i-1));
      }
    }
  }

  for (long long i = 0; i < mask_max; ++i) {
    if ((i & check_2[0]) != check_2[0]) {
      continue;
    }
    if ((i | check_1[0]) != check_1[0]) {
      continue;
    }
    dp[i][0] = 1;
  }

  for (long long j = 1; j < m; ++j) {
    for (long long i = 0; i < mask_max; ++i) {
        if ((i & check_2[j]) != check_2[j]) {
          continue;
        }

        if ((i | check_1[j]) != check_1[j]) {
          continue;
        }

        long long save_mask = i;
        long long mask_reverse = (1 << n) - 1 - save_mask;
        bool flag = true;
        long long prev = save_mask % 2;
        save_mask /= 2;
        for (int p = 0; p < n-1; ++p) {
          long long tek = save_mask % 2;
          if (tek == prev) {
            flag = false;
          }
          save_mask /= 2;
          prev = tek;
        }

        if (!flag) {
          dp[i][j] = dp[mask_reverse][j-1] % 1000000007;
        }
        else {
        dp[i][j] = (dp[i][j-1] + dp[mask_reverse][j-1]) % 1000000007;
      }
    }
  }
  /*
  for (long long i = 0; i < mask_max; ++i) {
    for (long long j = 0; j < m; ++j) {
      std::cout << dp[i][j] << " ";
    }
    std::cout << '\n';
  }
  */
  long long ans = 0;
  for (int i = 0; i < mask_max; ++i) {
    ans = (ans + dp[i][m-1]) % 1000000007;
  }
  std::cout << ans ;

  return 0;
}
