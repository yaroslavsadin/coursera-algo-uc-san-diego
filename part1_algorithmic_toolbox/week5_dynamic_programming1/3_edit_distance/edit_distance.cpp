#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;

int edit_distance(const string &str1, const string &str2) {
  static std::vector<std::vector<int>> dp_matrix(str1.size() + 1,std::vector<int>(str2.size() + 1));

  for(int i = 0; i < str1.size() + 1; i++) {
    dp_matrix[i][0] = i;
  }
  for(int i = 0; i < str2.size() + 1; i++) {
    dp_matrix[0][i] = i;
  }

  for(auto i = 1; i < str1.size() + 1; i++) {
    for(auto j = 1; j < str2.size() + 1; j++) {
      int penalty = static_cast<int>(str1[i-1] != str2[j-1]);
      dp_matrix[i][j] = std::min({
        dp_matrix[i][j-1] + 1,
        dp_matrix[i-1][j] + 1,
        dp_matrix[i-1][j-1] + penalty
      });
    }
  }

#ifdef DEBUG
  for(const auto& row : dp_matrix) {
    for(auto i : row) {
      std::cerr << i << '\t';
    }
    std::cerr << std::endl;
  }
#endif

  return dp_matrix[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
