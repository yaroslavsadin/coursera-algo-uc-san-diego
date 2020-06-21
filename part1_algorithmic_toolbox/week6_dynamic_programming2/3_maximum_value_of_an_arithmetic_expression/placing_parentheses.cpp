#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

class PlacingParens {
public:
  PlacingParens(std::vector<int> digits, std::vector<char> ops)
  : dp_table_min(digits.size(),std::vector<long long>(digits.size(),0)),
    dp_table_max(digits.size(),std::vector<long long>(digits.size(),0)),
    ops(std::move(ops))
  {
    for(size_t i = 0; i < digits.size(); i++) {
      dp_table_min[i][i] = digits[i];
      dp_table_max[i][i] = digits[i];
    }
  }

  long long Compute() {
    for(int diagonal = 1; diagonal < dp_table_max.size(); diagonal++) {
      for(int i = 0, j = diagonal; j < dp_table_max.size(); i++, j++) {
        Fill(i,j);
      }
    }
#ifdef DEBUG
    for(size_t i = 0; i < dp_table_max.size(); i++) {
      for(size_t j = 0; j < dp_table_max[i].size(); j++) {
        std::cerr << dp_table_max[i][j] << '\t';
      }
      std:: cerr << std::endl;
    }
    std:: cerr << std::endl;
    for(size_t i = 0; i < dp_table_min.size(); i++) {
      for(size_t j = 0; j < dp_table_min[i].size(); j++) {
        std::cerr << dp_table_min[i][j] << '\t';
      }
      std:: cerr << std::endl;
    }
#endif
    return dp_table_max[0].back();
  }
private:
  std::vector<std::vector<long long>> dp_table_min;
  std::vector<std::vector<long long>> dp_table_max;
  std::vector<char> ops;

  void Fill(size_t i, size_t j) {
    long long max_ = std::numeric_limits<long long>::min();
    long long min_ = std::numeric_limits<long long>::max();
    for(size_t k = i; k <= j - 1; k++) {
        auto MM = eval(dp_table_max[i][k],dp_table_max[k+1][j],ops[k]);
        auto Mm = eval(dp_table_max[i][k],dp_table_min[k+1][j],ops[k]);
        auto mM = eval(dp_table_min[i][k],dp_table_max[k+1][j],ops[k]);
        auto mm = eval(dp_table_min[i][k],dp_table_min[k+1][j],ops[k]);
        
        max_ = std::max(max_,std::max(std::max(MM,Mm),std::max(mM,mm)));
        min_ = std::min(min_,std::min(std::min(MM,Mm),std::min(mM,mm)));
    }
    dp_table_max[i][j] = max_;
    dp_table_min[i][j] = min_;
  }
};

long long get_maximum_value(const string &exp) {
  //write your code here
  std::vector<int> digits;
  std::vector<char> ops;
  for(size_t i = 0; i < exp.size(); i++) {
    if(i % 2) 
      ops.push_back(exp[i]);
    else
      digits.push_back(exp[i] - 0x30);
  }
  PlacingParens pp(std::move(digits),std::move(ops));
  return pp.Compute();
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
