#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class StringHasher {
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
	StringHasher(const string& s, const string& t) : 
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
	bool compare_substrings(int a, int b, int l) const {
		auto res = (
			((sh1[a+l] - pows_1[l] * sh1[a] % m1) + m1) % m1 == ((th1[b+l] - pows_1[l] * th1[b] % m1) + m1) % m1
			&&
			((sh2[a+l] - pows_2[l] * sh2[a] % m2) + m2) % m2 == ((th2[b+l] - pows_2[l] * th2[b] % m2) + m2) % m2
		);
#ifdef DEBUG
		assert((s.substr(a, l) == s.substr(b, l)) == res);
#endif
		return res;
	}

	const std::string& get_s() const {
		return s;
	}
	const std::string& get_t() const {
		return t;
	}
};

std::pair<int,int> find_next_mismatch(const StringHasher& hasher, int pos_text, int pos_pattern, int len) {
	int left = 0;
	int right = len + 1;
	while(right - left > 1) {
		int middle = (right + left) / 2;
#ifdef DEBUG
			std::cerr << "find_next_mismatch: " << hasher.get_s().substr(pos_text,middle) 
			<< ' ' << hasher.get_t().substr(pos_pattern,middle) << std::endl;
#endif
		if(hasher.compare_substrings(pos_text, pos_pattern, middle)) {
			left = middle;
		} else {
			right = middle;
		}
	}
	return (left == len) ? std::make_pair(-1,-1) : std::make_pair(pos_text + left, pos_pattern + left);	
}

vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> res;
	StringHasher hasher(text,pattern);
	for(size_t i = 0; i <= text.size() - pattern.size(); i++) {
		int mismatch_counter = 0;
		int len = pattern.size();
		int pos_text = i, pos_pattern = 0;
#ifdef DEBUG
		std::cerr << "----------------\n";
#endif
		while(mismatch_counter <= k) {
#ifdef DEBUG
			std::cerr << "Comparing: " << text.substr(pos_text,len) 
			<< ' ' << pattern.substr(pos_pattern,len) << std::endl;
#endif
			if(auto positions = find_next_mismatch(hasher,pos_text,pos_pattern,len); positions.first == -1) {
				res.push_back(i);
				break;
			} else {
#ifdef DEBUG
			std::cerr << "Mismatch: " << positions.first << ' ' << positions.second << std::endl;
#endif
				len -= positions.first + 1 - pos_text;
				pos_text = positions.first + 1;
				pos_pattern = positions.second + 1;
				mismatch_counter++;
			}
		}
#ifdef DEBUG
			std::cerr << "Mismatches: " << mismatch_counter << std::endl;
#endif
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
