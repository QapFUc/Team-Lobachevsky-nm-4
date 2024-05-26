#include "core/CGM.hpp"
#include "dataTypes/common.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

static void MatrixOperate(const std::vector<double>& A, const std::vector<double>& x, std::vector<double>& res, const size_t& width) {
    size_t i = 0, j = 0;
    size_t k = 0;
    double cX[5];
    for (size_t m = 0; m < x.size(); ++m) {
        i = m % width;
        j = m / width;
        k = 5 * m;
        cX[2] = x[i + j * width];

        j = j - 1;
        if (j < 0) {
            cX[0] = 0.l;
        } else {
            cX[0] = x[i + j * width];
        }

        i = i - 1;
        j += 1;
        if (i < 0) {
            cX[1] = 0.l;
        } else {
            cX[1] = x[i + j * width];
        }

        i = i + 2;
        if (i + j * width >= x.size()) {
            cX[3] = 0.l;
        } else {
            cX[3] = x[i + j * width];
        }

        i = i - 1;
        j = j + 1;
        if (i + j * width >= x.size()) {
            cX[4] = 0.l;
        } else {
            cX[4] = x[i + j * width];
        }

        res[m] = A[k] * cX[0] + A[k + 1] * cX[1] + A[k + 2] * cX[2] + A[k + 3] * cX[3] + A[k + 4] * cX[4];
    }
}

static void VectorSum(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1, const double& b = 1) {
    for (size_t k = 0; k < x.size(); ++k) {
        res[k] = a * x[k] + b * y[k];
    }
}

static void VectorSub(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1, const double& b = 1) {
    for (size_t k = 0; k < x.size(); ++k) {
        res[k] = a * x[k] - b * y[k];
    }
}

static double InnerProd(const std::vector<double>& x, const std::vector<double>& y) {
    double res = 0.l;
    for (size_t k = 0; k < x.size(); ++k) {
        res += x[k] * y[k];
    }
    return res;
}

static double EuclidianNormSq(const std::vector<double>& x) {
    return InnerProd(x, x);
}

std::vector<double> ConjGradMethod::eval() {
    std::vector<double> result(rhs.size());
    std::vector<double> direction(rhs.size());
    std::vector<double> residual(rhs.size());
    double alpha, beta, prod;

    // Start residual

    if (cfg.startX == nm::StartApr::Zeros) {
        for (auto& x : result)
            x = 0.l;
    }

    MatrixOperate(matrix, result, residual, cfg.matrix_width);
    VectorSub(rhs, residual, residual);

    // start direction

    direction = residual;

    double curr_tol = 1e15;
    size_t k = 0;
    std::vector<double> tmp(rhs.size());
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        MatrixOperate(matrix, direction, tmp, cfg.matrix_width);
        prod = InnerProd(residual, residual);
        alpha = prod / InnerProd(direction, tmp);
        VectorSum(result, direction, result, 1.l, alpha);

        VectorSub(residual, tmp, residual, 1.l, alpha);

        beta = InnerProd(residual, residual) / prod;

        VectorSum(residual, direction, direction, 1.l, beta);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        k++;
    }
    return result;
};