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

std::vector<double> ConjGradMethod::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
    std::vector<double> direction(rhs->size());
    std::vector<double> residual(rhs->size());
    std::vector<double> tmp(rhs->size());
    double alpha, beta, prod;

    // Start residual

    LOG_INFO_CLI("Init X");
    result = InitialX();

    LOG_INFO_CLI("Evaluating start residual");
    MatrixOperate(*matrix, result, residual, cfg.matrix_width);
    VectorSub(*rhs, residual, residual);

    // start direction

    direction = residual;

    double curr_tol = std::sqrt(EuclidianNormSq(residual));
    size_t k = 0;
    std::clock_t start;
    double duration = 0.l;
    LOG_INFO_CLI("Iterating CGM...");
    start = std::clock();
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        MatrixOperate(*matrix, direction, tmp, cfg.matrix_width);
        prod = InnerProd(residual, residual);
        alpha = prod / InnerProd(direction, tmp);
        VectorSum(result, direction, result, 1.l, alpha);

        VectorSub(residual, tmp, residual, 1.l, alpha);

        beta = InnerProd(residual, residual) / prod;

        VectorSum(residual, direction, direction, 1.l, beta);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        k++;
    }

    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;

    LOG_INFO_CLI("CGM Finished");
    std::cout << "Iterations total: " << k << " Elapsed time: " << duration <<  " Residual 2-norm: " << curr_tol << '\n';

    return result;
};