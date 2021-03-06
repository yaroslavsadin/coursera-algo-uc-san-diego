#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

string largest_number(vector<string> a) {
  //write your code here

  // If a + b > b + a and b + c > c + b => a + c > c + a
  std::sort(a.begin(),a.end(),
  [](const auto& lhs, const auto& rhs){
    // gcc bug? segfault when using >=
    return (lhs + rhs > rhs + lhs);
  });

  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
