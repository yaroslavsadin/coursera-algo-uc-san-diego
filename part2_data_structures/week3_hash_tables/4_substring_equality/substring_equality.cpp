#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class Solver {
	std::string s;
	std::vector<long long> h1, h2;
	std::vector<long long> pows_1, pows_2;
	const long long x;
	const long long m1, m2;

public:	
	Solver(string s) : 
	s(s), h1(s.size() + 1), h2(s.size() + 1), 
	pows_1(s.size() + 1), pows_2(s.size() + 1),
	x(rand() % static_cast<long long>(50) + 1), 
	m1(static_cast<long long>(std::pow(10,9)) + 7), 
	m2(static_cast<long long>(std::pow(10,9)) + 9) {	
		// initialization, precalculation
		for(size_t i = 1; i < h1.size(); i++) {
			h1[i] = (x * h1[i-1] + s[i-1] % m1 + m1) % m1;
		}
		for(size_t i = 1; i < h2.size(); i++) {
			h2[i] = (x * h2[i-1] + s[i-1] % m2 + m2) % m2;
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
	bool ask(int a, int b, int l) {
		auto res = (
			((h1[a+l] - pows_1[l] * h1[a] % m1) + m1) % m1 == ((h1[b+l] - pows_1[l] * h1[b] % m1) + m1) % m1
			&&
			((h2[a+l] - pows_2[l] * h2[a] % m2) + m2) % m2 == ((h2[b+l] - pows_2[l] * h2[b] % m2) + m2) % m2
		);
#ifdef DEBUG
		assert((s.substr(a, l) == s.substr(b, l)) == res);
#endif
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
