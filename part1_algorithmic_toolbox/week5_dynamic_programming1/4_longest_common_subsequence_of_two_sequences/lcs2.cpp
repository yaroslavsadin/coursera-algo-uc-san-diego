#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using std::vector;

std::vector<std::vector<int>> generate_subsequences(const vector<int> &original) {
  assert(original.size() <= 32);
  std::vector<std::vector<int>> res;
  for(uint32_t bitmask = 0x1; bitmask < std::pow(2,original.size()) && bitmask <= std::numeric_limits<uint32_t>::max(); bitmask++) {
    std::vector<int> subsequence;
    for(size_t i = 0; i < original.size(); i++) {
      if(bitmask & (1 << i)) {
        subsequence.push_back(original[i]);
      }
    }
    res.push_back(std::move(subsequence));
  }
  return res;
}

int lcs2_brute_force(vector<int> &a, vector<int> &b) {
  auto f_subsequences_equal = [](const std::vector<int>& a, const std::vector<int>& b) {
    if(a.size() != b.size()) {
      return false;
    }
    for(size_t k = 0; k < a.size(); k++) {
      if(a[k] != b[k]) {
        return false;
      }
    }
    return true;
  };

  std::vector<std::vector<int>> a_subsequences = generate_subsequences(a);
  std::vector<std::vector<int>> b_subsequences = generate_subsequences(b);
  size_t ans = 0;
  for(size_t i = 0; i < a_subsequences.size(); i++) {
    for(size_t j = 0; j < b_subsequences.size(); j++) {
      if(f_subsequences_equal(a_subsequences[i],b_subsequences[j])) {
        ans = std::max(ans,a_subsequences[i].size());
      }
    }
  }

  return ans;
}

template<typename It>
int f_lcs2_recurse(It a_begin, It a_end, It b_begin, It b_end) {
    if(a_begin == a_end || b_begin == b_end) {
      return 0;
    }
    if(*prev(a_end) == *prev(b_end)) {
      return 1 + f_lcs2_recurse(a_begin,prev(a_end),b_begin,prev(b_end));
    }
    return std::max(
      f_lcs2_recurse(a_begin,a_end,b_begin,prev(b_end)),
      f_lcs2_recurse(a_begin,prev(a_end),b_begin,b_end)
    );
  };

int lcs2_recursive_naive(vector<int> &a, vector<int> &b) {
  //write your code here
  return f_lcs2_recurse(a.begin(),a.end(),b.begin(),b.end());
}

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  std::vector<std::vector<int>> dp_matrix(a.size()+1,std::vector<int>(b.size() + 1, 0));

  for(int i = 1; i < dp_matrix.size(); i++) {
    for(int j = 1; j < dp_matrix[i].size(); j++) {
      if(a[i-1] == b[j-1]) {
        dp_matrix[i][j] = dp_matrix[i-1][j-1] + 1;
      } else {
        dp_matrix[i][j] = std::max(
          dp_matrix[i-1][j],
          dp_matrix[i][j-1]
        );
      }
    }
  }
#ifdef DEBUG
  for(int i = 0; i < dp_matrix.size(); i++) {
    for(int j = 0; j < dp_matrix[i].size(); j++) {
      std::cerr << dp_matrix[i][j] << ' ';
    }
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
#endif

  return dp_matrix.back().back();
}

int main() {
#ifdef ENABLE_STRESS_TEST
  while(1) {
    size_t n = rand() % 8 + 1;
    std:: cerr << n << std::endl;
    std::vector<int> a(n);
    
    for(auto& i : a) {
      i = rand() % 10 + 1;
      std:: cerr << i << ' ';
    }

    size_t m = rand() % 8 + 1;
    std:: cerr << std::endl << m << std::endl;
    std::vector<int> b(m);
    for(auto& i : b) {
      i = rand() % 10 + 1;
      std:: cerr << i << ' ';
    }
    std::cerr << std::endl;
    assert(lcs2_recursive_naive(a, b) == lcs2(a, b));
    std::cerr << "OK\n";
  }
#endif
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
