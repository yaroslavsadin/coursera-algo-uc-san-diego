#include <iostream>
#ifdef DEBUG
#include "test_runner.h"
#include "profile_advanced.h"


TotalDuration naive("naive");
TotalDuration fast("fast");
#endif

int gcd_naive(int a, int b) {
#ifdef DEBUG
    ADD_DURATION(naive);
#endif
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
#ifdef DEBUG
    ADD_DURATION(fast);
#endif
  if(b == 0) {
    return a;
  }
  return gcd_fast(b,a%b);
}

#ifdef DEBUG
void TestGcd() {
    for(auto i = 1; i < 999; i++) {
      for(auto j = 1; j < 999; j++) {
        ASSERT_EQUAL(gcd_naive(i,j), gcd_fast(i,j));
      }
    }
}
#endif

int main() {
#ifdef DEBUG
    TestRunner tr;
    RUN_TEST(tr,TestGcd);
#endif

  int a, b;
  std::cin >> a >> b;
  // std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
