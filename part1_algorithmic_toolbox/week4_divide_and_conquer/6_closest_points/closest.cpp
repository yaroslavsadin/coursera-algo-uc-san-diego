#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>

using std::vector;
using std::string;
using std::pair;
using std::min;

struct Point {
  int x;
  int y;
};

double calc_distance(Point lhs, Point rhs) {
  return std::sqrt(std::pow(lhs.x - rhs.x,2) + std::pow(lhs.y - rhs.y,2));
}

template<typename It>
double minimal_distance_impl(It begin_, It end_) {
  auto size_ = std::distance(begin_,end_);

  if(size_ == 2) {
    return calc_distance(*begin_, *std::next(begin_));
  }

  auto middle = begin_ + size_ / 2;

  auto min_ = std::min(
    minimal_distance_impl(begin_,(std::next(begin_) == middle) ? std::next(middle) : middle),
    minimal_distance_impl(middle,end_)
  );

  std::vector<Point> y_sorted_l(begin_, middle);
  std::vector<Point> y_sorted_r(middle, end_);
  
  size_t l_idx = 0;
  size_t r_idx = 0;
  for(auto it = y_sorted_l.begin(); it != y_sorted_l.end(); it++) {
    while(it->y > y_sorted_r[r_idx].y && r_idx < y_sorted_r.size()) {
      r_idx++;
    }
    for(size_t i = 0; i < 7 && i + r_idx < y_sorted_r.size(); i++) {
      min_ = std::min(min_,calc_distance(*it,y_sorted_r[r_idx + i]));
    }
  }
  for(auto it = y_sorted_r.begin(); it != y_sorted_r.end(); it++) {
    while(it->y > y_sorted_l[l_idx].y && l_idx < y_sorted_l.size()) {
      l_idx++;
    }
    for(size_t i = 0; i < 7 && i + l_idx < y_sorted_l.size(); i++) {
      min_ = std::min(min_,calc_distance(*it,y_sorted_l[l_idx + i]));
    }
  }
  return min_;
}

double minimal_distance(const vector<int> x, vector<int> y) {
  //write your code here
  std::vector<Point> points(x.size());
  auto it_x = x.begin();
  auto it_y = y.begin();
  for(auto& p : points) {
    p = {*it_x++,*it_y++};
  }
  std::sort(points.begin(),points.end(),
  [](auto lhs, auto rhs){
    return lhs.y < rhs.y;
  });
  return minimal_distance_impl(points.begin(), points.end());
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
