#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::string;
typedef unsigned long long ull;

long long hash_func(const string& s, size_t prime, size_t multiplier) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i] % prime + prime) % prime;
    return hash;
}

std::vector<long long> precompute_hashes(const string& t, size_t length, size_t prime, size_t multiplier) {
    std::vector<long long> res(t.size() - length + 1);
    res.back() = hash_func(t.substr(t.size() - length, length),prime,multiplier);
    long long y = 1;
    for(size_t i = 0; i < length; i++) {
        y = y * multiplier % prime;
    }
    for(int i = t.size() - length - 1; i >= 0; i--) {
        res[i] = (multiplier * res[i+1] + t[i] - y * t[i+length] % prime + prime) % prime;
#ifdef DEBUG
        auto hash_check = hash_func(t.substr(i, length),prime,multiplier);
        std::cerr << i << ' ' << res[i] << ' ' << hash_check << std::endl;
        assert(res[i] == hash_check);
#endif
    }
    return res;
}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    static const size_t multiplier = 263;
    static const size_t prime = 2500000000000343;
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    auto pHash = hash_func(s,prime,multiplier);
    auto H = precompute_hashes(t,s.size(),prime,multiplier);
    for (size_t i = 0; i + s.size() <= t.size(); ++i) {
        if(pHash != H[i])
            continue;
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
