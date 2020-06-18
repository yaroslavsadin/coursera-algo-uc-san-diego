#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here
  std::vector<std::vector<std::vector<int>>> dp_matrix(
    a.size() + 1,
    std::vector<std::vector<int>>(
      b.size() + 1, std::vector<int>(
        c.size() + 1, 0
      )
    )
  );

  for(int i = 1; i < dp_matrix.size(); i++) {
    for(int j = 1; j < dp_matrix[i].size(); j++) {
      for(int k = 1; k < dp_matrix[i][j].size(); k++) {
        if(a[i-1] == b[j-1] && b[j-1] == c[k-1]) {
          dp_matrix[i][j][k] = dp_matrix[i-1][j-1][k-1] + 1;
        } else {
          std::array<int,3> choices;
          choices[0] = dp_matrix[i][j][k-1];
          choices[1] = dp_matrix[i][j-1][k];
          choices[2] = dp_matrix[i-1][j][k];

          dp_matrix[i][j][k] = *std::max_element(choices.begin(),choices.end());
        }
      }
    }
  }
#if 0
  std::vector<int> res;
  for(int i = dp_matrix.size()-1, j = dp_matrix[i].size()-1; i > 0 && j > 0;) {
    if(dp_matrix[i][j] - dp_matrix[i-1][j-1] == 1) {
      res.push_back(a[i-1]);
      i--; j--;
    } else {
      if(dp_matrix[i][j-1] == dp_matrix[i][j]) {
        j--;
      } else {
        i--;
      }
    }
  }

  std::reverse(res.begin(),res.end());
#endif
  return dp_matrix.back().back().back();
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
