#include <iostream>
#include <vector>
#include <array>

// Replacing c++17 std::optional
class OptionalInt {
public:
  OptionalInt() = default;
  OptionalInt& operator=(int a) {
    value = a;
    defined = true;
    return *this;
  }
  bool IsDefined() const {
    return defined;
  }
  int& operator*() {
    return value;
  }
  const int& operator*() const {
    return value;
  }
private:
  bool defined = false;
  int value = 0;
};

int get_change(int m) {
  //write your code here
  constexpr std::array<int,3> coins {1,3,4};
  std::vector<OptionalInt> changes(m + 1);
  changes[0] = 0;
  for(int i = 1; i <= m; i++) {
    for(auto coin : coins) {
      if(i >= coin) {
        if(!changes[i].IsDefined()) {
          changes[i] = *changes[i-coin] + 1;
        } else {
          changes[i] = std::min(*changes[i],*changes[i-coin] + 1);
        }
      }
    }
#ifdef DEBUG
    for(const auto& change : changes) {
      std::cerr << *change << ' ';
    }
    std::cerr << std::endl;
#endif
  }
  return *changes.back();
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
