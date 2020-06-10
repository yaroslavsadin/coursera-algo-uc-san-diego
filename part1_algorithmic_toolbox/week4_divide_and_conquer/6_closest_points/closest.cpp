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
  enum class Part {
    LEFT, RIGHT
  } part;
};

double calc_distance(Point lhs, Point rhs) {
  return std::sqrt(std::pow(lhs.x - rhs.x,2) + std::pow(lhs.y - rhs.y,2));
}

template<typename It>
double minimal_distance_impl(It begin_, It end_) {
  auto size_ = std::distance(begin_,end_);
  assert(size_ >= 2);
  if(size_ == 2) {
    return calc_distance(*begin_, *std::next(begin_));
  }
  auto middle = begin_ + size_ / 2;
  auto min_ = std::min(
    minimal_distance_impl(begin_,(std::next(begin_) == middle) ? std::next(middle) : middle),
    minimal_distance_impl(middle,end_)
  );
  std::vector<Point> y_sorted(begin_, end_);
  for(size_t i = 0; i < y_sorted.size(); i++) {
    if(i < std::distance(begin_, middle)) {
      y_sorted[i].part = Point::Part::LEFT;
    } else {
      y_sorted[i].part = Point::Part::RIGHT;
    }
  }
  std::sort(y_sorted.begin(),y_sorted.end(),
  [](auto lhs, auto rhs){
    return lhs.y < rhs.y;
  });
  for(size_t i = 0; i < y_sorted.size(); i++) {
    size_t scanned = 0;
    for(size_t j = i + 1; scanned < 7 && j < y_sorted.size(); j++) {
      if(y_sorted[i].part != y_sorted[j].part) {
        min_ = std::min(min_,calc_distance(y_sorted[i],y_sorted[j]));
        scanned++;
      }
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
    return lhs.x < rhs.x;
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
