#include <iostream>
#include <vector>

struct matrix {
    std::size_t rows_;
    std::size_t cols_;
    std::vector<double> data_;
    double& operator()(std::size_t i, std::size_t j) noexcept {
        return data_[i * cols_ + j];
    }
    const double& operator()(std::size_t i, std::size_t j) const noexcept {
        return data_[i * cols_ + j];
    }
};

matrix operator*(const matrix &l, const matrix &r) {
    matrix res{l.rows_, r.cols_, std::vector<double>(l.rows_ * r.cols_)};
    for (std::size_t i = 0; i < l.rows_; ++i) {
#ifdef REORDER
        for (std::size_t k = 0; k < l.cols_; ++k) {
            for (std::size_t j = 0; j < r.cols_; ++j) {
#else
        for (std::size_t j = 0; j < r.cols_; ++j) {
            for (std::size_t k = 0; k < l.cols_; ++k) {
#endif
                res(i, j) += l(i, k) * r(k, j);
            }
        }
    }
    return res;
}

int main() {
    for (std::size_t i = 16; i <= 256; ++i) {
        std::vector<double> a(i * i);
        for (std::size_t j = 0; j < a.size(); ++j) {
            a[j] = j;
        }
        const matrix m {i, i, a};
        const matrix prod = m * m;
    }
    return 0;
}
