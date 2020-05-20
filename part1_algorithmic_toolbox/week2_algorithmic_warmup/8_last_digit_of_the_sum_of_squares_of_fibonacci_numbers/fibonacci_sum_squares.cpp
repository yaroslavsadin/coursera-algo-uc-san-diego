#include <iostream>
#include <array>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
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

int fibonacci_sum_squares_fast(long long n) {
    if (n <= 1)
        return n;

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
    // Sum(Fn^2) = Fn*Fn+1
    auto Fn = (fibonacci_squaring(q_matrix,n,f_mx_mul_last_digit)[1]);
    auto Fnp1 = (fibonacci_squaring(q_matrix,n + 1,f_mx_mul_last_digit)[1]);
    return Fn*Fnp1 % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
