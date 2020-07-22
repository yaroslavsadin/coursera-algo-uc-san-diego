#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>

using namespace std;

struct Answer {
	size_t i, j, len;
};

class Solver {
	const std::string& s, t;
	std::vector<long long> sh1, sh2;
	std::vector<long long> th1, th2;
	std::vector<long long> pows_1, pows_2;

	static constexpr long long x {49};
	static constexpr auto m1 {1000000000 + 7};
	static constexpr auto m2 {1000000000 + 9};

	long long GetSubstringHash1(int a, int l, const std::vector<long long>& source) const {
		return ((source[a+l] - pows_1[l] * source[a] % m1) + m1) % m1;
	}
	long long GetSubstringHash2(int a, int l, const std::vector<long long>& source) const {
		return ((source[a+l] - pows_2[l] * source[a] % m2) + m2) % m2;
	}
public:	
	Solver(const string& s, const string& t) : 
	s(s), t(t), sh1(s.size() + 1), sh2(s.size() + 1), th1(t.size() + 1), th2(t.size() + 1), 
	pows_1(s.size() + 1), pows_2(s.size() + 1){	
		// initialization, precalculation
		for(size_t i = 1; i < th1.size(); i++) {
			th1[i] = (x * th1[i-1] + t[i-1] % m1 + m1) % m1;
		}
		for(size_t i = 1; i < th2.size(); i++) {
			th2[i] = (x * th2[i-1] + t[i-1] % m2 + m2) % m2;
		}
		for(size_t i = 1; i < sh1.size(); i++) {
			sh1[i] = (x * sh1[i-1] + s[i-1] % m1 + m1) % m1;
		}
		for(size_t i = 1; i < sh2.size(); i++) {
			sh2[i] = (x * sh2[i-1] + s[i-1] % m2 + m2) % m2;
		}
		pows_1[0] = 1;
		for(size_t i = 1; i < pows_1.size(); i++) {
			pows_1[i] = (pows_1[i-1] * x % m1 + m1) % m1;
		}
		pows_2[0] = 1;
		for(size_t i = 1; i < pows_2.size(); i++) {
			pows_2[i] = (pows_2[i-1] * x % m2 + m2) % m2;
		}
	}
	Answer ask(int l) {
		std::unordered_map<long long, int> hash_to_idx;
		for(int i = 0; i + l <= s.size(); i++) {
			auto sh1_ = GetSubstringHash1(i,l,sh1);
			auto sh2_ = GetSubstringHash2(i,l,sh2);
			hash_to_idx[sh1_] = i;
			hash_to_idx[sh2_] = i;
		}
		for(int i = 0; i + l <= t.size(); i++) {
			auto th1_ = GetSubstringHash1(i,l,th1);
			auto th2_ = GetSubstringHash2(i,l,th2);
			if(hash_to_idx.count(th1_) && hash_to_idx.count(th2_)) {
				return {hash_to_idx.at(th1_),i,l};
			}
		}
		return {0,0,0};
	}
};

Answer solve(const string &s, const string &t) {
	Solver solver(s,t);
	auto low = 0;
	auto high = std::min(s.size(),t.size())+1;
	Answer res = {0,0,0};
	while (high - low > 1) {
		int len = (low + high) / 2;
#ifdef DEBUG
		std::cerr << "High: " << high << ", Low: " << low << ", Len: " << len << std::endl;
#endif
		if(auto candidate = solver.ask(len); candidate.len > 0) {
			res = (candidate.len > res.len) ? candidate : res;
			low = len;
		} else {
			high = len;
		}
	}
	
	return res;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
