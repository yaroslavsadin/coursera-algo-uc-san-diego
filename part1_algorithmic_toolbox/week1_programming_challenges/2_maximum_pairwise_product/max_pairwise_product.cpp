#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

size_t MaxPairwiseProduct(const std::vector<size_t>& numbers) {
    size_t max_product = 0;
    size_t n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    }

    return max_product;
}

size_t MaxPairwiseProductFast(const std::vector<size_t>& numbers) {
    if(!numbers.size()) {
        return 0;
    } else if(numbers.size() == 1) {
        return numbers[0];
    }
    
    std::vector<size_t> res;
    res.resize(2);
    std::partial_sort_copy(
        numbers.begin(),numbers.end(),res.begin(),res.end(),
        std::greater<size_t>()
    );
    return res[0] * res[1];
}

int main() {
#if 0
    while (1)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        const auto n = (rand() % 1000) + 1;
        std::vector<size_t> input(n,0);
        std:: cerr << "Input: ";
        for(auto& i : input) {
            i = (rand() % 10000) + 1;
            std:: cerr << i << ' ';
        }
        std:: cerr << std::endl;
        auto res_naive = MaxPairwiseProduct(input);
        auto res_fast = MaxPairwiseProductFast(input);
        std::cerr << res_naive << ' ' << res_fast << std::endl;
        assert(res_naive == res_fast);
        std:: cerr << "OK" << std::endl;
    }
#endif
    int n;
    std::cin >> n;
    std::vector<size_t> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProductFast(numbers) << "\n";
    return 0;
}
