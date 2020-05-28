#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <unordered_set>
#include <set>
#include <cmath>
#include <sstream>
#include <cassert>
#include <iomanip>

using std::vector;

struct Segment {
  int start, end;
};

bool is_within(int point, Segment segment) {
  return point >= segment.start && point <= segment.end;
}

vector<int> optimal_points_attempt_1(vector<Segment> segments) {
  vector<int> points;
  //write your code here
  
  std::vector<int> left_ends; left_ends.reserve(segments.size());
  for(size_t i = 0; i < segments.size(); i++) {
    left_ends.push_back(i);
  }
  std::sort(left_ends.begin(),left_ends.end(),
  [&segments](int lhs, int rhs) {
    return segments[lhs].start < segments[rhs].start;
  });

  std::vector<int> right_ends; right_ends.reserve(segments.size());
  for(size_t i = 0; i < segments.size(); i++) {
    right_ends.push_back(i);
  }
  std::sort(right_ends.begin(),right_ends.end(),
  [&segments](int lhs, int rhs) {
    return segments[lhs].end < segments[rhs].end;
  });

  auto f_max_intersection = []
  (const std::vector<int>& left_ends, const std::vector<int>& right_ends, const vector<Segment> &segments) {
    std::unordered_set<int> res_intersection;
    int res_point = 0;

    for(int i = segments[*left_ends.begin()].start; i <= segments[*prev(right_ends.end())].end; i++) {
      std::unordered_set<int> intersection;
      for(size_t j = 0; j < segments.size(); j++) {
        if(is_within(i,segments[j])) {
          intersection.insert(j);
        }
      }
      if(res_intersection.size() < intersection.size()) {
        res_intersection = intersection;
        res_point = i;
      }
    }
    return std::pair<int,std::unordered_set<int>>{res_point,std::move(res_intersection)};
  };

  while(segments.size()) {
      auto intersection = f_max_intersection(left_ends,right_ends,segments);
      if(!intersection.second.size()) {
        for(auto segment : segments) {
          points.push_back(segment.start);
        }
        break;
      } else {
        points.push_back(intersection.first);
        {
          auto it = std::remove_if(left_ends.begin(),left_ends.end(),[&intersection](auto elem) {
            return intersection.second.count(elem);
          });
          left_ends.erase(it,left_ends.end());
        }
        {
          auto it = std::remove_if(right_ends.begin(),right_ends.end(),[&intersection](auto elem) {
            return intersection.second.count(elem);
          });
          right_ends.erase(it,right_ends.end());
        }
        {
          auto it = std::remove_if(segments.begin(),segments.end(),[&intersection](auto elem) {
            return is_within(intersection.first,elem);
          });
          segments.erase(it,segments.end());
        }
      }
  }

  return points;
}

void Draw(Segment segment, std::ostream& os = std::cerr) {
  for(int i = 0; i < segment.start; i++) {
    os << "  ";
  }
  for(int i = segment.start; i < segment.end; i++) {
    os << "==";
  }
}

vector<int> optimal_points_attempt_2(vector<Segment> segments) {
  vector<int> points;
  //write your code here

  std::vector<int> left_ends; left_ends.reserve(segments.size());
  for(size_t i = 0; i < segments.size(); i++) {
    left_ends.push_back(i);
  }
  std::sort(left_ends.begin(),left_ends.end(),
  [&segments](int lhs, int rhs) {
    return segments[lhs].start < segments[rhs].start;
  });
#ifdef DEBUG
  for(size_t i = 0; i < left_ends.size(); i++) {
    std::cerr << std::setw(2) << std::setfill('0') << left_ends[i] << ": ";
    Draw(segments[left_ends[i]]);
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
#endif

  std::vector<int> right_ends; right_ends.reserve(segments.size());
  for(size_t i = 0; i < segments.size(); i++) {
    right_ends.push_back(i);
  }
  std::sort(right_ends.begin(),right_ends.end(),
  [&segments](int lhs, int rhs) {
    return segments[lhs].end < segments[rhs].end;
  });
#ifdef DEBUG
  for(size_t i = 0; i < right_ends.size(); i++) {
    std::cerr << std::setw(2) << std::setfill('0') << right_ends[i] << ": ";
    Draw(segments[right_ends[i]]);
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
#endif

  auto f_max_intersection = []
  (const std::vector<int>& left_ends, const std::vector<int>& right_ends, const vector<Segment> &segments) {
    std::set<int> res_intersection;
    int res_point = 0;
    int prev_count = 0;

    std::set<int> intersection;
    size_t left_idx = 0; size_t right_idx = 0;
#ifdef DEBUG
    std::cerr << "f_max_intersection start" << std::endl;
#endif
    while(right_idx < right_ends.size()) {
      auto current_point = (left_idx < left_ends.size()) ? std::min(
        segments[left_ends[left_idx]].start, segments[right_ends[right_idx]].end + 1
      ) : segments[right_ends[right_idx]].end + 1;

      while(left_idx < left_ends.size() && segments[left_ends[left_idx]].start == current_point) {
        intersection.insert(left_ends[left_idx++]);
      }
      while(right_idx < right_ends.size() && segments[right_ends[right_idx]].end + 1 == current_point) {
        intersection.erase(right_ends[right_idx++]);
      }
#ifdef DEBUG
      std::cerr << current_point << ": " <<'[';

      for(int i : intersection) {
        std::cerr << i << ' ';
      }
      std::cerr << ']' << ' ' << intersection.size() << std::endl;
#endif
      if(res_intersection.size() <= intersection.size()) {
        res_intersection = intersection;
        res_point = current_point;
      }
    }
    return std::pair<int,std::set<int>>{res_point,std::move(res_intersection)};
  };

  while(left_ends.size()) {
    auto intersection = f_max_intersection(left_ends,right_ends,segments);
    if(intersection.second.size() == 1) {
      for(auto left_idx : left_ends) {
        points.push_back(segments[left_idx].start);
      }
      break;
    } else {
      points.push_back(intersection.first);

      auto it = std::remove_if(left_ends.begin(),left_ends.end(),[&intersection](auto elem) {
        return intersection.second.count(elem);
      });
      left_ends.erase(it,left_ends.end());

      it = std::remove_if(right_ends.begin(),right_ends.end(),[&intersection](auto elem) {
        return intersection.second.count(elem);
      });
      right_ends.erase(it,right_ends.end());
    }
  }

  return points;
}

vector<int> optimal_points_attempt_3(vector<Segment> segments) {
  vector<int> points;

  std::sort(segments.begin(),segments.end(),
  [](auto lhs, auto rhs) {
    return lhs.end < rhs.end;
  });
  
  points.push_back(segments.begin()->end);
  for(auto it = segments.begin(); it != segments.end(); it++) {
    if(it->start > points.back()) {
      points.push_back(it->end);
    }
  }

  return points;
}

int main() {
#if ENABLE_STRESS_TEST
  while (1)
  {
      srand(static_cast<unsigned int>(time(nullptr)));
      const auto n = (rand() % 20) + 1;
      std::cerr << "n: " << n << std:: endl;
      std::vector<Segment> input(n,{0,0});

      for(auto& i : input) {
          i.start = (rand() % 10) + 1;
          i.end = i.start + (rand() % 10) + 1;
          std:: cerr << i.start << ' ' << i.end << std::endl;
      }
      std::cerr << std::endl;

      vector<int> points_naive = optimal_points_attempt_1(input);
      vector<int> points = optimal_points_attempt_2(input);
      std:: cerr << "Naive: " << points_naive.size() << ", " << "Opt: " << points.size() << std::endl;
      assert(points_naive.size() == points.size());
  }
#endif
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points_attempt_3(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
  return 0;
}
