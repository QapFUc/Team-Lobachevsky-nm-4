#include "core/CGM.hpp"
#include <cmath>
#include <cstddef>
#include <numeric>
#include <vector>

static void MatrixOperate(const std::vector<double>& A, const std::vector<double>& x, std::vector<double> res, const size_t& width) {
    size_t i = 0, j = 0;

    res[0] = A[2] * x[0] + A[3] * x[1] + A[4] * x[width];
    res[1] = A[6] * x[0] + A[7] * x[1] + A[8] * x[2] + A[9] * x[width + 1];

    size_t k = 0;
    for (size_t m = 2; m < x.size() - 2; ++m) {
        k = 5 * m;
        i = m % width;
        if (i == 0)
            j++;

        res[m] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width] + A[k + 3] * x[i + 1 + j * width] +
                 A[k + 4] * x[i + (j + 1) * width];
    }

    k += 5;
    i = (x.size() - 2) % width;
    if (i == 0)
        j++;
    res[x.size() - 2] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width] + A[k + 3] * x[i + 1 + j * width];
    k += 5;
    i = (x.size() - 1) % width;
    if (i == 0)
        j++;
    res[x.size() - 1] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width];
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

    MatrixOperate(matrix, cfg.startX, residual, cfg.matrix_width);
    VectorSub(rhs, residual, residual);
    ;

    // start direction

    direction = residual;

    double curr_tol = 1e15;
    size_t k = 0;
    std::vector<double> tmp(rhs.size());
    while (curr_tol >= cfg.tolerance) {
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
}