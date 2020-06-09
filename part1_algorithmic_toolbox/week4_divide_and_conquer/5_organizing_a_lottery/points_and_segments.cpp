#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct Segment {
  int start;
  int end;
};

/// XXX: for some reason iterative version is much slower
template<typename It>
vector<int> fast_count_segments_impl(const vector<Segment>& segments_sorted_left, const vector<Segment>& segments_sorted_right, It points_begin, It points_end) {
  auto size_ = std::distance(points_begin,points_end);
  vector<int> cnt;
  //write your code here
  // O(s/2)
  if(size_ == 1) {
    cnt.resize(1);
    // Determine the closest end to the point
    if(std::abs(segments_sorted_left.front().start - *points_begin) < std::abs(*points_begin - segments_sorted_right.back().end)) {
      // Scan from left
      for(int i = 0; i < segments_sorted_left.size() && segments_sorted_left[i].start <= *points_begin; i++) {
        if(segments_sorted_left[i].end >= *points_begin) {
          cnt[0]++;
        }
      }
    } else {
      // Scan from write
      for(int i = segments_sorted_right.size() - 1; i >= 0  && *points_begin <= segments_sorted_right[i].end; i--) {
        if(segments_sorted_right[i].start <= *points_begin) {
          cnt[0]++;
        }
      }
    }

  } else {
    auto middle = points_begin + size_ / 2;
    auto left_ = fast_count_segments_impl(segments_sorted_left,segments_sorted_right,points_begin,middle);
    auto right_ = fast_count_segments_impl(segments_sorted_left,segments_sorted_right,middle,points_end);
    std::swap(cnt,left_);
    cnt.insert( cnt.end(), right_.begin(), right_.end() );
  }
  return cnt;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  std::vector<Segment> segments_sorted_left(starts.size());
  for(size_t i = 0; i < segments_sorted_left.size(); i++) {
    segments_sorted_left[i] = {starts[i],ends[i]};
  }
  std::vector<Segment> segments_sorted_right(segments_sorted_left.begin(),segments_sorted_left.end());
  std::sort(segments_sorted_left.begin(),segments_sorted_left.end(),
  [](auto lhs, auto rhs){
    return lhs.start < rhs.start;
  });
  std::sort(segments_sorted_right.begin(),segments_sorted_right.end(),
  [](auto lhs, auto rhs){
    return lhs.end < rhs.end;
  });
  return fast_count_segments_impl(segments_sorted_left,segments_sorted_right,points.begin(),points.end());
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
