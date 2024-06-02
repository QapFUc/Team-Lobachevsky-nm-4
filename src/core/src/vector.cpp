#include "core/vector.hpp"
#include <cstddef>

void MatrixOperate(const std::vector<double>& A, const std::vector<double>& x, std::vector<double>& res, const std::vector<size_t>& widthes) {
    size_t i = 0, j = 0;
    size_t k = 0, L = 0;
    double cX[5];
    int64_t s = widthes[L];
    for (size_t m = 0; m < x.size(); ++m) {
        if (m > s) {
            L++;
            s += widthes[L];
        }

        size_t width = widthes[L];
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

void VectorSum(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a, const double& b) {
    for (size_t k = 0; k < x.size(); ++k) {
        res[k] = a * x[k] + b * y[k];
    }
}

void VectorSub(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a, const double& b) {
    for (size_t k = 0; k < x.size(); ++k) {
        res[k] = a * x[k] - b * y[k];
    }
}

double InnerProd(const std::vector<double>& x, const std::vector<double>& y) {
    double res = 0.l;
    for (size_t k = 0; k < x.size(); ++k) {
        res += x[k] * y[k];
    }
    return res;
}

double EuclidianNormSq(const std::vector<double>& x) {
    return InnerProd(x, x);
}

double InfNormVector(const std::vector<double>& x,const std::vector<double>& y) {
    double res = 0.l;
    for (size_t k = 0; k < x.size(); ++k) {
        if (res < std::abs(x[k] - y[k])){
            res = std::abs(x[k] - y[k]);
        }
    }
    return res;
}