#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;

// O(n)
bool check_majority_subrange(const vector<int> &a, int left, int right, int value) {
  auto size_ = (right-left);
  int cnt = 0;
  for(auto i = left; i <= right; i++) {
    if(a[i] == value) {
      cnt++;
    }
    if(cnt == size_/2 + 1) {
      return true;
    }
  }
  return false;
}

// T(n) = 2T(n/2) + O(n) => O(n*log(n)) 
int get_majority_element(vector<int> &a, int left, int right) {
#ifdef DEBUG
  std::cerr << "left: " << left << ", " << "right: " << right;
  std::cerr << std::endl;
#endif
  if (right-left <= 2) { 
    return a[left];
  }
  auto middle = left + (right-left)/2; 
  auto left_ = get_majority_element(a,left,middle);
  if(left_ != -1 && check_majority_subrange(a, left, right, left_)) {
    return left_;
  }
  auto right_ = get_majority_element(a,middle + 1,right);
  if(right_ != -1 && check_majority_subrange(a, left, right, right_)) {
    return right_;
  }
  return -1;
}

// O(n) + O(n) = O(n)
int get_majority_element_faster(vector<int> &a, int left, int right) {
  std::unordered_map<int,int> counter;
  for(auto i : a) {
    counter[i]++;
  }
  for(const auto& p : counter) {
    if(p.second > a.size()/2) {
      return p.first;
    }
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element_faster(a, 0, a.size()) != -1) << '\n';
}
