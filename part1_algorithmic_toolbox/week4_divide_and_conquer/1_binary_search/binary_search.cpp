#include <iostream>
#include <cassert>
#include <vector>
#include <iterator>

using std::vector;

template<typename It>
It binary_search_impl(It begin_, It end_, int x) {
  static_assert(std::is_same<typename std::iterator_traits<It>::value_type,int>::value);
  if(begin_ == end_) {
    return end_;
  } else if(*begin_ == x) {
    return begin_;
  }
  It middle = begin_ + std::distance(begin_,end_)/2;
  return (x > *middle) ? binary_search_impl(next(middle),end_,x) : binary_search_impl(begin_,middle,x) ;
}

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size(); 
  //write your code here
  auto it = binary_search_impl(a.begin(),a.end(),x);
  if(it == a.end() || *it != x) {
    return -1;
  }
  return std::distance(a.begin(),it);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
