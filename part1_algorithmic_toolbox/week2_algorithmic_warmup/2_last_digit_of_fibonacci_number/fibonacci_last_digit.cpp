#include <iostream>
#ifdef DEBUG
#include "test_runner.h"
#include "profile_advanced.h"


TotalDuration naive("naive");
TotalDuration fast("fast");
#endif

int get_fibonacci_last_digit_naive(int n) {
#ifdef DEBUG
    ADD_DURATION(naive);
#endif
    if (n <= 1)
        return n;

    size_t previous = 0;
    size_t current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        size_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
#ifdef DEBUG
    ADD_DURATION(fast);
#endif
    if (n <= 1)
        return n;
    
    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    return current;
}
#ifdef DEBUG
void TestFibLastDigit() {
    for(auto i = 0; i < 93; i++) {
        ASSERT_EQUAL(get_fibonacci_last_digit_fast(i), get_fibonacci_last_digit_naive(i));
    }
}
#endif
int main() {
#ifdef DEBUG
    TestRunner tr;
    RUN_TEST(tr,TestFibLastDigit);
#endif
    int n;
    std::cin >> n;
    // int c = get_fibonacci_last_digit_naive(n);
    // std::cout << c << '\n';
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
    }
