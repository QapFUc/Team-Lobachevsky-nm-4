#include "core/CGM.hpp"
#include "dataTypes/common.hpp"
#include <cmath>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>
#include "core/vector.hpp"
#include "nm/utils/logger.hpp"
#include "nm/utils/profiler.hpp"

std::vector<double> ConjGradMethod::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
    std::vector<double> direction(rhs->size());
    std::vector<double> residual(rhs->size());
    double alpha, beta, prod;

    // Start residual

    LOG_INFO_CLI("Set start approach");
    if (cfg.startX == nm::StartApr::Zeros) {
        for (auto& x : result)
            x = 0.l;
    }

    LOG_INFO_CLI("Evaluating start residual");
    MatrixOperate(*matrix, result, residual, cfg.matrix_width);
    VectorSub(*rhs, residual, residual);

    // start direction

    direction = residual;

    double curr_tol = 1e15;
    size_t k = 0;
    double percentage = 0.l;
    double perc_step = (1.l / cfg.Max_N);
    std::vector<double> tmp(rhs->size());
    LOG_INFO_CLI("Iterating CGM...");
    std::cout << percentage * 100.l << "\% done ";
    std::clock_t start;
    double duration = 0.l;
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        start = std::clock();
        MatrixOperate(*matrix, direction, tmp, cfg.matrix_width);
        prod = InnerProd(residual, residual);
        alpha = prod / InnerProd(direction, tmp);
        VectorSum(result, direction, result, 1.l, alpha);

        VectorSub(residual, tmp, residual, 1.l, alpha);

        beta = InnerProd(residual, residual) / prod;

        VectorSum(residual, direction, direction, 1.l, beta);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        k++;

        duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
        percentage += perc_step;
        std::cout << '\r' << percentage * 100.l << "\% done " << ". Estimation time (approx): " << duration * (cfg.Max_N - k) << " s" <<  std::flush;
    }

    std::cout << '\n';
    std::cout << "Total tolerance: " << curr_tol << '\n';
    LOG_INFO_CLI("CGM finished");
    return result;
};