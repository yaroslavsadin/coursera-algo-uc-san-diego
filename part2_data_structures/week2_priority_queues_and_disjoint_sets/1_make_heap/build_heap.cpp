#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int LeftNodeIdx(size_t i) const {
    auto idx = 2*i + 1;
    if(idx < data_.size()) {
      return idx;
    }
    return -1;
  }

  int RightNodeIdx(size_t i) const {
    auto idx = 2*i + 2;
    if(idx < data_.size()) {
      return idx;
    }
    return -1;
  }

  int MinLeafIdx(size_t i) const {
    int left_idx = LeftNodeIdx(i);
    int right_idx = RightNodeIdx(i);
    if(left_idx == -1 && right_idx == -1) {
        return -1;
    }
    if(left_idx != -1 && right_idx == -1) {
      return left_idx;
    }
    if(left_idx == -1 && right_idx != -1) {
      return right_idx;
    }
    if(data_[left_idx] < data_[right_idx]) {
      return left_idx;
    }
    return right_idx;
  }

  void SiftDown(size_t i) {
    for(auto leaf_idx = MinLeafIdx(i); leaf_idx != -1; leaf_idx = MinLeafIdx(i)) {
      if(leaf_idx != -1 && data_[leaf_idx] < data_[i]) {
        std::swap(data_[i],data_[leaf_idx]);
        swaps_.push_back(std::make_pair(i,leaf_idx));
        i = leaf_idx;
      } else {
        break;
      }
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = data_.size() / 2; i >= 0 ; --i) {
      SiftDown(i);
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
