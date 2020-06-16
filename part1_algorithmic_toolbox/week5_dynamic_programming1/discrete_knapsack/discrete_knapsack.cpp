#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::unordered_map<int,int> weight_to_val;

int knapsack_with_repitions(const std::vector<int>& values, const std::vector<int>& weights, int W) 
{
    if(!weight_to_val.count(W)) {
        weight_to_val[W] = 0;
    }
    for(size_t i = 0; i < weights.size(); i++) {
        if(weights[i] <= W) {
            weight_to_val[W] = std::max(
                weight_to_val[W],
                knapsack_with_repitions(values,weights,W-weights[i]) + values[i]
            );
        }
    }
#ifdef DEBUG
    for(const auto& [w,v] : weight_to_val) {
        std::cerr << w << ' ' << v << std::endl;
    }
    std::cerr << "---------------------" << std::endl;
#endif
    return weight_to_val[W];
}

int knapsack_iterative(const std::vector<int>& values, const std::vector<int>& weights, int W, bool repititions_mode = false) {
    std::vector<std::vector<int>> dp_matrix(weights.size()+1,std::vector<int>(W+1));

    for(size_t i = 1; i < weights.size() + 1; i++) {
        for(size_t j = 1; j < W + 1; j++) {
            int taking_profit = 0;
            if(j >= weights[i-1]) {
                taking_profit = std::max(
                    // taking from the current row in repititions mode
                    (repititions_mode) ? values[i-1] + dp_matrix[i][j-weights[i-1]] : 0,
                    // taking from the upper row
                    values[i-1] + dp_matrix[i-1][j-weights[i-1]]
                );
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
    return dp_matrix[weights.size()][W];
}

int main(void) {
    // std::vector<int> weights = {6 , 3 , 4 , 2 };
    std::vector<int> weights = {3, 4, 5, 6 };
    // std::vector<int> values = {30, 14, 16 , 9};
    std::vector<int> values = {2, 3, 4 , 1};
    int W = 8;
    std::cout << knapsack_iterative(values,weights,W,true) << std::endl;
    return 0;
}