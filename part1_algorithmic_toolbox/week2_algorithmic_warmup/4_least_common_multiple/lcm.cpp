#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#ifdef DEBUG
#include "test_runner.h"
#include "profile_advanced.h"


TotalDuration naive("naive");
TotalDuration fast("fast");
TotalDuration faster("faster");
#endif

long long lcm_naive(int a, int b) {
#ifdef DEBUG
    ADD_DURATION(naive);
#endif
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {
#ifdef DEBUG
    ADD_DURATION(fast);
#endif
  auto max_input = std::max(a,b);
  for (long long l = max_input; l <= (long long) a * b; l += max_input) {
    if (l % a == 0 && l % b == 0) {
      return l;
    }
  }

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
  if(b == 0) {
    return a;
  }
  return gcd_fast(b,a%b);
}

long long lcm_faster(int a, int b) {
#ifdef DEBUG
    ADD_DURATION(faster);
#endif
  return a*static_cast<long long>(b) / gcd_fast(a,b);
}

#ifdef DEBUG
void TestLcm() {
    for(auto i = 1; i < 100; i++) {
      for(auto j = 1; j < 100; j++) {
        ASSERT_EQUAL(lcm_naive(i,j), lcm_fast(i,j));
        ASSERT_EQUAL(lcm_naive(i,j), lcm_faster(i,j));
      }
    }
}

void TestMaxInt() {
  lcm_fast(std::numeric_limits<int>::max() / 2,std::numeric_limits<int>::max() / 5);
  lcm_faster(std::numeric_limits<int>::max() / 2,std::numeric_limits<int>::max() / 5);
}
#endif

int main() {
#ifdef DEBUG
    {
      TestRunner tr;
      RUN_TEST(tr,TestLcm);
      RUN_TEST(tr,TestMaxInt);
    }
#endif

  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  // std::cout << lcm_fast(a, b) << std::endl;
  std::cout << lcm_faster(a, b) << std::endl;
  return 0;
}
