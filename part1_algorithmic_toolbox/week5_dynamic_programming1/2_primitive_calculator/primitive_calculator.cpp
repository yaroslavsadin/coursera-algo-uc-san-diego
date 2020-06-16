#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;

class primitive_calculator
{
private:
  std::vector<int> sequence;
  std::vector<int> ways;
public:
  primitive_calculator(int n) : sequence(), ways(n+1) {}
  ~primitive_calculator() {}
  std::vector<int> compute() {
    for(int i = ways.size()-1; i > 0; i--) {  
      ways[i] = compute_recurse(i);
    }
#ifdef DEBUG
    for(auto i : ways) {
      std::cerr << i << ' ';
    }
    std::cerr << std::endl;
#endif
    sequence.push_back(ways.size()-1);
    for(int i = ways.size()-1; i != 1;) {
      if(i % 2 == 0 && ways[i/2] == ways[i] - 1) {
        i /= 2;
      } else if(i % 3 == 0 && ways[i/3] == ways[i] - 1) {
        i /= 3;
      } else { // if(dp_array[i-1] == dp_array[i] - 1)
        i--;
      }
      sequence.push_back(i);
    }
    std::reverse(sequence.begin(),sequence.end());
    return sequence;
  }
  int compute_recurse(int n) {
    if(n == 1) {
      return 0;
    }
    int optimal_ways = compute_recurse(n-1) + 1;
    if(n % 2 == 0) {
      optimal_ways = std::min(compute_recurse(n/2) + 1,optimal_ways);
    }
    if(n % 3 == 0) {
      optimal_ways = std::min(compute_recurse(n/3) + 1,optimal_ways);
    }
    return optimal_ways;
  }
};

vector<int> optimal_sequence_naive(int n) {
  primitive_calculator calc(n);
  return calc.compute();
}

vector<int> optimal_sequence(int n) {
  if(n == 0) return {};

  std::vector<int> sequence;
  std::vector<int> dp_array(n+1);

  for(size_t i = 1; i < dp_array.size(); i++) {
    int final_cost = dp_array[i-1] + 1;

    if(i % 2 == 0) {
      final_cost = std::min(dp_array[i/2] + 1,final_cost);
    }
    if(i % 3 == 0) {
      final_cost = std::min(dp_array[i/3] + 1,final_cost);
    }

    dp_array[i] = final_cost;
  }
#ifdef DEBUG
    for(auto i : dp_array) {
      std::cerr << i << ' ';
    }
    std::cerr << std::endl;
#endif
  sequence.push_back(n);
  for(int i = n; i != 1;) {
    if(i % 2 == 0 && dp_array[i/2] == dp_array[i] - 1) {
      i /= 2;
    } else if(i % 3 == 0 && dp_array[i/3] == dp_array[i] - 1) {
      i /= 3;
    } else { // if(dp_array[i-1] == dp_array[i] - 1)
      i--;
    }
    sequence.push_back(i);
  }
  std::reverse(sequence.begin(),sequence.end());
  return sequence;
}

int main() {
#ifdef ENABLE_STRESS_TEST
  for(int i = 1; i < 30; i++) {
    vector<int> sequence_naive = optimal_sequence_naive(i);
    vector<int> sequence = optimal_sequence(i);
    if(sequence_naive.size() != sequence.size()) {
      std::cerr << "Fail, n = " << i <<std::endl;
      exit(-1);
    }
  }
  std::cerr << "OK" << std::endl;
#endif
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
