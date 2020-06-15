#include <iostream>
#include <vector>
#include <string>
#include <optional>

void lis_recurse(const std::vector<int>& input, size_t idx, std::vector<std::optional<std::vector<int>>>& dp_array) {
    if(idx == input.size() || dp_array[idx]) return;
    const std::vector<int>* rhs = nullptr;
    for(auto i = idx + 1; i < input.size(); i++) {
        if(input[idx] < input[i]) {
            lis_recurse(input,i,dp_array);
            if(rhs == nullptr || rhs->size() < dp_array[i]->size()) {
                rhs = &*dp_array[i];
            }
        }
    }
    std::vector<int> res;
    res.push_back(input[idx]);
    if(rhs) {
        std::copy(rhs->begin(),rhs->end(),std::back_inserter(res));
    }
    dp_array[idx] = std::move(res);
}

std::vector<int> lis_top(const std::vector<int>& input) {
    std::vector<std::optional<std::vector<int>>> dp_array(input.size());
    std::optional<size_t> res_idx = 0;
    for(size_t i = 0; i < input.size(); i++) {
        lis_recurse(input,i,dp_array);
        if(!res_idx || dp_array[*res_idx]->size() < dp_array[i]->size()) {
            res_idx = i;
        }
#ifdef DEBUG
    for(const auto& str : dp_array) {
        if(str.has_value()) {
            for(int i : *str)    
                std::cout << i;
            std::cout << '\t';
        } else {
            std::cerr << "+" << '\t';
        }
    }
    std::cerr << std::endl << "----------" << std::endl;
#endif
    }
    return *dp_array[*res_idx];
}

int main(void) {
    std::vector<int> test_seq = {50, 3, 10, 7, 40, 80};
    for(int i : lis_top(test_seq))    
        std::cout << i << ' ';
    std::cout << std::endl;
    return 0;
}