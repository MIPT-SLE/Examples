#include <chrono>
#include <random>

// requires c++23
#include <print>

int main() {
    using clock         = std::chrono::high_resolution_clock;
    const std::size_t n = 10'000'000;
    std::vector<double> a(n);
    std::vector<double> b(n);

    std::mt19937_64 engine{std::random_device{}()};
    std::uniform_real_distribution uniform;
    const auto generate = [&engine, &uniform] { return uniform(engine); };

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = uniform(engine);
        b[i] = uniform(engine);
    }

    auto start = clock::now();
    for (std::size_t i = 0; i < n; ++i) {
        volatile double c = 0;
        c                 = a[i] + b[i];
    }
    auto stop      = clock::now();
    const auto sum = stop - start;

    start = clock::now();
    for (std::size_t i = 0; i < n; ++i) {
        volatile double c = 0;
        c                 = a[i] * b[i];
    }
    stop               = clock::now();
    const auto product = stop - start;

    start = clock::now();
    for (std::size_t i = 0; i < n; ++i) {
        volatile double c = 0;
        c                 = std::sin(a[i]);
    }
    stop           = clock::now();
    const auto sin = stop - start;

    std::println("sum: {}\nprd: {}\nsin: {}", sum, product, sin);

    return 0;
}