#include <iostream>
#include <vector>
#include <map>
#include <functional>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  std::map<double,int,std::greater<>> values_per_weights;
  for(auto i = 0u; i < weights.size(); i++) {
    values_per_weights[static_cast<double>(values[i])/weights[i]] = weights[i];
  }
  for(auto& [value_per_weight,total_weight] : values_per_weights) {
    if(capacity >= total_weight) {
      // Taking the whole item
      value += value_per_weight*total_weight;
      capacity -= total_weight;
    } else {
      // Taking the last piece
      value += capacity*value_per_weight;
      break;
    }
  }
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
