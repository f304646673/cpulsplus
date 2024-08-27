#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <functional>
 
namespace with_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n <= 0) [[unlikely]]
            return 1;
        else [[likely]]
            return x * pow(x, n - 1);
    }
} // namespace with_attributes
 
namespace no_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n <= 0)
            return 1;
        else
            return x * pow(x, n - 1);
    }
} // namespace no_attributes

double calc(double x, std::function<double(double, long long)> f) noexcept {
    constexpr long long precision{16LL};
    double y{};
    for (auto n{0LL}; n < precision; n += 2LL)
        y += f(x, n);
    return y;
}

double gen_random() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0, 1.0);
    return dis(gen);
}
 
volatile double sink{}; // ensures a side effect
 
int main() {
    auto benchmark = [](auto fun, auto rem)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        for (auto y{1ULL}; y != 500'000'000ULL; ++y)
            sink = calc(gen_random(), fun);
        const std::chrono::duration<double> diff =
            std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
                  << " sec " << rem << std::endl; 
    };
 
    benchmark(with_attributes::pow, "(with attributes)");
    benchmark(no_attributes::pow, "(without attributes)");
    benchmark(with_attributes::pow, "(with attributes)");
    benchmark(no_attributes::pow, "(without attributes)");
    benchmark(with_attributes::pow, "(with attributes)");
    benchmark(no_attributes::pow, "(without attributes)");
}