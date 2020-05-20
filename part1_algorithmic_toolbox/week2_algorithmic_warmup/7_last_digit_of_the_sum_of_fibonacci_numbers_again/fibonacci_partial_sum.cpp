#include <iostream>
#include <vector>
#include <array>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

// Using exponenentiation by squearing algorithm
// to obtain N-th fibonacci number in O(logN)
template<typename Matrix, typename Func>
auto fibonacci_squaring(Matrix m, long long n, const Func& f_mx_mul) {
    if(n == 1) {
        return m;
    } else if(n % 2) {
        return f_mx_mul(fibonacci_squaring(f_mx_mul(m,m),(n-1)/2,f_mx_mul),m);
    } else {
        return fibonacci_squaring(f_mx_mul(m,m),n/2,f_mx_mul);
    }
    return m;
}

int get_fibonacci_partial_sum_fast(long long from, long long to) {
    if(from == 0 && to == 0)
        return 0;

    static constexpr std::array<int,4> q_matrix = 
    {
        1, 1,
        1, 0
    };

    static const auto f_mx_mul_last_digit = [](auto matrix1, auto matrix2) {
        auto a1 = matrix1[0]; auto a2 = matrix2[0];
        auto b1 = matrix1[1]; auto b2 = matrix2[1];
        auto c1 = matrix1[2]; auto c2 = matrix2[2];
        auto d1 = matrix1[3]; auto d2 = matrix2[3];

        decltype(matrix1) res;

        // Getting two last digits, need for carry over case
        res[0] = (a1*a2 + b1*c2)%100;
        res[1] = (a1*b2 + b1*d2)%100;
        res[2] = (a2*c1 + c2*d1)%100;
        res[3] = (b2*c2 + d1*d2)%100;

        return res;
    };

    if (from == to)
        return fibonacci_squaring(q_matrix,from,f_mx_mul_last_digit)[1] % 10;

    // Sum(Fn to Fm) = Sum(Fn) - Sum(Fm)
    auto Sfrom = fibonacci_squaring(q_matrix,from + 1,f_mx_mul_last_digit)[1];
    auto Sto = fibonacci_squaring(q_matrix,to + 2,f_mx_mul_last_digit)[1];
    // + 100 to guarantee that Sto is larger than Sfrom for potential digit stealing
    return (Sto + 100 - Sfrom) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
