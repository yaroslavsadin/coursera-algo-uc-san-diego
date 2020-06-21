#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

template<typename It>
long long Sum(It begin_, It end_) {
  long long acc = 0;
  for(; begin_ != end_; begin_++) {
    acc += *begin_;
  }
  return acc;
}

// This already passes the grader :)
int partition3_brute_force(vector<int> &A) {
  //write your code here
  auto total_sum = Sum(A.begin(),A.end());
  if(total_sum % 3) {
    return 0;
  }
  do {
    for(auto it_1 = A.begin(); it_1 != A.end(); it_1++) {
      for(auto it_2 = std::next(it_1); it_2 != A.end(); it_2++) {
        long long sum_a = Sum(A.begin(),it_1);
        long long sum_b = Sum(it_1,it_2);
        long long sum_c = Sum(it_2,A.end());
        if(sum_a == sum_b && sum_b == sum_c) {
          return 1;
        }
      }
    }
  } while(std::next_permutation(A.begin(),A.end()));
  return 0;
}

std::pair<int,std::vector<int>> knapsack_iterative(const std::vector<int>& values, const std::vector<int>& weights, int W) {
    std::vector<std::vector<int>> dp_matrix(weights.size()+1,std::vector<int>(W+1));

    for(size_t i = 1; i < weights.size() + 1; i++) {
        for(size_t j = 1; j < W + 1; j++) {
            int taking_profit = 0;
            if(j >= weights[i-1]) {
                taking_profit = values[i-1] + dp_matrix[i-1][j-weights[i-1]];
            }
            dp_matrix[i][j] = std::max(
                taking_profit,
                dp_matrix[i-1][j] // not taking
            );
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
    std::vector<int> res;
    for(size_t i = dp_matrix.size() - 1, j = dp_matrix[i].size() - 1; j != 0 && i != 0; i--) {
      if(dp_matrix[i][j] == values[i-1] + dp_matrix[i-1][j-weights[i-1]]) {
        j -= weights[i-1];
        res.push_back(i-1);
      }
    }
    return {dp_matrix.back().back(),res};
}

int partition3(vector<int> &A) {
  //write your code here

  // For sorted array we can use the knapsack algorithm to find the solution for each bucket
  std::sort(A.begin(),A.end());

  auto total_sum = Sum(A.begin(),A.end());
  if(total_sum % 3) {
    return 0;
  }
  for(int i = 0; i < 3; i++) {
    auto partition = knapsack_iterative(A,A,total_sum/3);
#ifdef DEBUG
    for(auto idx : partition.second) {
      std::cerr << A[idx] << ' ';
    }
    std::cerr << std::endl;
#endif
    if(partition.first != total_sum/3) {
      return 0;
    }
    for(auto idx : partition.second) {
      A.erase(A.begin() + idx);
    }
  }
  return 1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
