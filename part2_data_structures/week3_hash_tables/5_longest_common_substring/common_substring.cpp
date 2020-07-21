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
	std::string s, t;
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
	Solver(string s, string t) : 
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
#ifdef DEBUG
		std::cerr << "Length: " << l << ":\n";
#endif
		for(int i = 0; i + l <= s.size(); i++) {
			auto sh1_ = GetSubstringHash1(i,l,sh1);
			auto sh2_ = GetSubstringHash2(i,l,sh2);
#ifdef DEBUG
			std::cerr << "i: " << i << ", sh1: " << sh1_ << ", sh2: " << sh2_ << std::endl;
#endif
			for(int j = 0; j + l <= t.size(); j++) {
#ifdef DEBUG
				std::cerr << "j: " << j << ", th1: " << GetSubstringHash1(j,l,th1) << ", th2: " << GetSubstringHash2(j,l,th2) << std::endl;
#endif
				if(sh1_ == GetSubstringHash1(j,l,th1) && sh2_ == GetSubstringHash2(j,l,th2)) {
					return {i,j,l};
				}
			}
		}
		return {0,0,0};
	}
};

Answer solve(const string &s, const string &t) {
	Solver solver(s,t);
	auto max_len = std::min(s.size(),t.size());
	Answer ans{0,0,0};
	for(int l = 1; l <= max_len; l++) {
		auto candidate = solver.ask(l);
		if(candidate.len > 0) {
			ans = candidate;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
