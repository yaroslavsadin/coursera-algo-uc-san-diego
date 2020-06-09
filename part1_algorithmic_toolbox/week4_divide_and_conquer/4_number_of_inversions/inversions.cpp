#include <iostream>
#include <vector>

using std::vector;

// long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
//   long long number_of_inversions = 0;
//   if (right <= left + 1) return number_of_inversions;
//   size_t ave = left + (right - left) / 2;
//   number_of_inversions += get_number_of_inversions(a, b, left, ave);
//   number_of_inversions += get_number_of_inversions(a, b, ave, right);
//   //write your code here
//   return number_of_inversions;
// }

template<typename It>
long long Merge(It begin_first, It end_first, It begin_second, It end_second) {
  long long inversion_counter = 0;
#ifdef DEBUG
  for(auto it = begin_first; it != end_first; it++) {
    std::cerr << *it << ' ';
  }
  std::cerr << " *** ";
  for(auto it = begin_second; it != end_second; it++) {
    std::cerr << *it << ' ';
  }
  std::cerr << std::endl;
#endif
  // O(first.size * second.size) time, could do better by scanning from the end. Passes the tests though.
  for(auto it1 = begin_first; it1 != end_first; it1++) {
    for(auto it2 = begin_second; it2 != end_second; it2++) {
      if(*it1 > *it2) inversion_counter++;
    }
  }
  std::vector<typename std::iterator_traits<It>::value_type> temp;
  temp.reserve(std::distance(begin_first,end_first)*2);
  auto it_first = begin_first;
  auto it_second = begin_second;
  while(it_first != end_first && it_second != end_second) {
    if(*it_first > *it_second) {
      temp.push_back(*it_second++);
    } else {
      temp.push_back(*it_first++);
    }
  }
  if(it_first != begin_second) {
    std::move(it_first,end_first,std::back_inserter(temp));
  }
  if(it_second != end_second) {
    std::move(it_second,end_second,std::back_inserter(temp));
  }
  size_t i = 0;
  while(begin_first != end_first) {
    *begin_first++ = std::move(temp[i++]);
  }
  while(begin_second != end_second) {
    *begin_second++ = std::move(temp[i++]);
  }
  return inversion_counter;
}

template<typename It>
long long MergeSort(It begin_, It end_) {
  auto size_ = std::distance(begin_,end_);
  if(size_ <= 1) return 0;
  long long inversion_counter = 0;
  auto mid = begin_ + size_ / 2;
  inversion_counter += MergeSort(begin_,mid);
  inversion_counter += MergeSort(mid,end_);
  inversion_counter += Merge(begin_,mid,mid,end_);
  return inversion_counter;
}


int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << MergeSort(a.begin(),a.end()) << '\n';
  for (size_t i = 0; i < a.size(); i++) {
    std::cerr << a[i] << ' ';
  }
  std::cerr << std:: endl;
}
