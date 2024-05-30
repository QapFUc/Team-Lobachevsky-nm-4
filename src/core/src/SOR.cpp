#include "core/SOR.hpp"
#include "core/vector.hpp"
#include "nm/utils/logger.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <numeric>
#include <ostream>
#include <vector>

#define PI 3.14159265358979

static double GetOutDiagSumm(const size_t& m, const std::vector<size_t>& widthes, const std::vector<double>& x, const std::vector<double>& A) {
    size_t i = 0, j = 0;
    size_t k = 0, L = 0;
    double cX[4];

    size_t s = widthes[L];
    while (m > s) {
        L++;
        s += widthes[L];
    }

    
    size_t width = widthes[L];
    i = m % width;
    j = m / width;
    k = 5 * m;

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
        cX[2] = 0.l;
    } else {
        cX[2] = x[i + j * width];
    }

    i = i - 1;
    j = j + 1;
    if (i + j * width >= x.size()) {
        cX[3] = 0.l;
    } else {
        cX[3] = x[i + j * width];
    }

    return A[k] * cX[0] + A[k + 1] * cX[1] + A[k + 3] * cX[2] + A[k + 4] * cX[3];
}

std::vector<double> SuccessiveOverRelax::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
    std::vector<double> residual(rhs->size());
    double ksq = 1.l / (*matrix)[4];
    double hsq = 1.l / (*matrix)[3];
    double k = std::sqrt(ksq);
    double h = std::sqrt(hsq);
    double lamdasq = 1.l - 2.l * (ksq * std::pow(std::sin(PI * h / (2.l * cfg.n)), 2) + hsq * std::pow(std::sin(PI * k / (2.l * cfg.m)), 2)) / (ksq + hsq);
    lamdasq *= lamdasq;
    double omega = 2 / (1 + std::sqrt(1 - lamdasq));

    LOG_INFO_CLI("Init X");
    result = InitialX();

    LOG_INFO_CLI("Evaluating start residual");
    MatrixOperate(*matrix, result, residual, cfg.net_widthes);
    VectorSub(*rhs, residual, residual);

    double curr_tol = std::sqrt(EuclidianNormSq(residual));
    double omegaInv = (1 / omega - 1);

    size_t l = 0;
    std::clock_t start;
    double duration = 0.l;
    LOG_INFO_CLI("Iterating SOR...");
    start = std::clock();
    while (curr_tol >= cfg.tolerance && l < cfg.Max_N) {
        for (size_t m = 0; m < result.size(); ++m) {
            result[m] = (omega / (*matrix)[2]) * (omegaInv * (*matrix)[2] * result[m] - GetOutDiagSumm(m, cfg.net_widthes, result, *matrix) + (*rhs)[m]);
        }

        MatrixOperate(*matrix, result, residual, cfg.net_widthes);
        VectorSub(*rhs, residual, residual);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        l++;
    }

    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
    LOG_INFO_CLI("SOR Finished");
    std::cout << "Selected omega: " << omega << " Iterations total: " << l << " Elapsed time: " << duration << " Residual 2-norm: " << curr_tol << '\n';

    return result;
}