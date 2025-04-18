#include <chrono>
#include <format>
#include <iostream>
#include <vector>

struct RowMajorMatrix {
    std::size_t         rows;
    std::size_t         cols;
    std::vector<double> data;

    double& operator()(std::size_t i, std::size_t j) noexcept {
        return data[i * cols + j];
    }
    double operator()(std::size_t i, std::size_t j) const noexcept {
        return data[i * cols + j];
    }
};

struct ColMajorMatrix {
    std::size_t         rows;
    std::size_t         cols;
    std::vector<double> data;

    double& operator()(std::size_t i, std::size_t j) noexcept {
        return data[i + j * rows];
    }
    double operator()(std::size_t i, std::size_t j) const noexcept {
        return data[i + j * rows];
    }
};

std::vector<double> dot(const RowMajorMatrix& m, const std::vector<double>& v) {
    std::vector<double> res(m.rows);
    for (std::size_t i = 0; i < m.rows; ++i) {
        for (std::size_t j = 0; j < m.cols; ++j) {
            res[i] += m(i, j) * v[j];
        }
    }
    return res;
}

std::vector<double> dot(const ColMajorMatrix& m, const std::vector<double>& v) {
    std::vector<double> res(m.rows);
    for (std::size_t i = 0; i < m.rows; ++i) {
        for (std::size_t j = 0; j < m.cols; ++j) {
            res[i] += m(i, j) * v[j];
        }
    }
    return res;
}

std::vector<double> getVector(std::size_t n) {
    std::vector<double> res(n);
    for (std::size_t i = 0; i < n; ++i) {
        res[i] = i + 1;
    }
    return res;
}

int main() {
    using clock         = std::chrono::high_resolution_clock;

    const auto rowStart = clock::now();
    for (std::size_t i = 10; i < 100; ++i) {
        RowMajorMatrix      m{.rows = i, .cols = i, .data = getVector(i * i)};
        std::vector<double> v   = getVector(i);
        const auto          res = dot(m, v);
    }
    const auto rowStop  = clock::now();

    const auto colStart = clock::now();
    for (std::size_t i = 10; i < 100; ++i) {
        ColMajorMatrix      m{.rows = i, .cols = i, .data = getVector(i * i)};
        std::vector<double> v   = getVector(i);
        const auto          res = dot(m, v);
    }
    const auto colStop = clock::now();

    std::cout << std::format("Row-major: {}\n", rowStop - rowStart);
    std::cout << std::format("Col-major: {}\n", colStop - colStart);
    std::cout << std::flush;

    return 0;
}
