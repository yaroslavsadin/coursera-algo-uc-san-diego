#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;

struct SegPoint {
  enum class Type {
    START, END
  } type;
  int value;
};

// Sweep line approach, O(nlogn) + O(mlogm)
vector<int> fast_count_segments_take_two(const vector<int>& starts, const vector<int>& ends, vector<int> points) {
  vector<int> cnt(points.size());
  
  std::vector<SegPoint> seg_points;
  seg_points.reserve(starts.size()*2);
  for(auto i : starts) {
    seg_points.push_back({SegPoint::Type::START,i});
  }
  for(auto i : ends) {
    seg_points.push_back({SegPoint::Type::END,i});
  }
  std::sort(seg_points.begin(),seg_points.end(),
  [](auto lhs, auto rhs) {
    return lhs.value < rhs.value;
  });
  
  std::vector<size_t> points_idxs(points.size());
  for(int i = 0; i < points.size(); i++) {
    points_idxs[i] = i;
  }
  std::sort(points_idxs.begin(),points_idxs.end(),
  [&points](auto lhs, auto rhs) {
    return points[lhs] < points[rhs];
  });

  int counter = 0;
  auto points_it = points_idxs.begin();
  auto seg_points_it = seg_points.begin();
  for(int i = std::min(points[*points_it],seg_points_it->value); 
          points_it != points_idxs.end() && seg_points_it != seg_points.end();
          i = std::min(points[*points_it],seg_points_it->value))
  {
    size_t num_starts = 0;
    size_t num_ends = 0;
    while(seg_points_it != seg_points.end() && i == seg_points_it->value) {
      if(seg_points_it->type == SegPoint::Type::START) {
        num_starts++;
      } else {
        num_ends++;
      }
      seg_points_it++;
    }
    counter += num_starts;
    while(points_it != points_idxs.end() && i == points[*points_it]) {
      cnt[*points_it] = counter;
      points_it++;
    }
    counter -= num_ends;
    if(points_it == points_idxs.end() || seg_points_it == seg_points.end()) {
      break;
    }
  }
  return cnt;
}



struct Segment {
  int start;
  int end;
};

// This is still O(n*m) but passes the grader!
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

vector<int> fast_count_segments_take_one(vector<int> starts, vector<int> ends, vector<int> points) {
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
#if ENABLE_STRESS_TEST
  while (1)
  {
      srand(static_cast<unsigned int>(time(nullptr)));
      const auto n = (rand() % 50) + 1;
      const auto m = (rand() % 60) + 1;
      std::cerr << n << ' ' << m << std::endl;

      vector<int> starts(n), ends(n);
      for (size_t i = 0; i < starts.size(); i++) {
        starts[i] = (rand() % 250) + 1;
        ends[i] = starts[i] + (rand() % 250) + 1;
        std::cerr << starts[i] << ' ' << ends[i] << std::endl;
      }
      vector<int> points(m);
      for (size_t i = 0; i < points.size(); i++) {
        points[i] = (rand() % 500) + 1;
        std::cerr << starts[i] << ' ';
      }
      std::cerr << std::endl;

      auto res_naive = naive_count_segments(starts, ends, points);
      auto res = fast_count_segments_sweep_line(starts, ends, points);
      
      for(size_t i = 0; i < points.size(); i++) {
        assert(res[i] == res_naive[i]);
      }
  }
#endif
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
  vector<int> cnt = fast_count_segments_take_two(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
