#include "core/CGM.hpp"
#include "core/vector.hpp"
#include "dataTypes/common.hpp"
#include "nm/utils/logger.hpp"
#include "nm/utils/profiler.hpp"
#include <cmath>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

static double InfNorm(const std::vector<double>& x) {
    double res = 0l;

    for (const auto& comp : x) {
        if (std::abs(comp) > res) res = std::abs(comp);
    }

    return res;
}

std::vector<double> ConjGradMethod::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
    std::vector<double> diff(rhs->size());
    std::vector<double> direction(rhs->size());
    std::vector<double> residual(rhs->size());
    std::vector<double> tmp(rhs->size());
    double alpha, beta, prod;

    // Start residual

    LOG_INFO_CLI("Init X");
    result = InitialX();

    LOG_INFO_CLI("Evaluating start residual");
    MatrixOperate(*matrix, result, residual, cfg.net_widthes);
    VectorSub(*rhs, residual, residual);
    std::cout << "Initial residual 2-norm (R(0)) = " << std::sqrt(EuclidianNormSq(residual)) << '\n';

    // start direction

    direction = residual;

    double curr_tol = 1e14;
    double resid_norm = 0l;
    size_t k = 0;
    std::clock_t start;
    double duration = 0.l;
    LOG_INFO_CLI("Iterating CGM...");
    start = std::clock();
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        exCfg.prevsol = result;
        MatrixOperate(*matrix, direction, tmp, cfg.net_widthes);
        prod = InnerProd(residual, residual);
        alpha = prod / InnerProd(direction, tmp);
        VectorSum(result, direction, result, 1.l, alpha);

        VectorSub(residual, tmp, residual, 1.l, alpha);

        beta = InnerProd(residual, residual) / prod;

        VectorSum(residual, direction, direction, 1.l, beta);
        resid_norm = std::sqrt(EuclidianNormSq(residual));
        k++;

        VectorSub(result, exCfg.prevsol, diff);
        curr_tol = InfNorm(diff);
    }
    exCfg.N = k;
    exCfg.tolerance = curr_tol;
    exCfg.solution = result;
    exCfg.Methodtolerance = curr_tol;

    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;

    LOG_INFO_CLI("CGM Finished");
    std::cout << "---Total results---\n";
    std::cout << "Required tolerance: " << cfg.tolerance << '\n' << "Result tolerance: " << curr_tol << '\n' << "Iterations total: " << k << '\n' << "Elapsed time: " << duration << '\n' << "Residual 2-norm: " << resid_norm << '\n';

    return result;
}