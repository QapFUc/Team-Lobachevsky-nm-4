#include "core/SimpleIter.hpp"
#include "core/vector.hpp"
#include "dataTypes/common.hpp"
#include "nm/utils/logger.hpp"
#include <ctime>
#include <iostream>
#include <vector>

std::vector<double> SimpleIter::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
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
    double curr_tol = std::sqrt(EuclidianNormSq(residual));
    size_t k = 0;

    LOG_INFO_CLI("Iterating SimpleIter...");
    std::clock_t start;
    double duration = 0.l;
    double parametr = (1.l / (2 * (*matrix)[2] - 1));
    start = std::clock();
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        VectorSum(result, residual, result, 1.l, parametr);

        MatrixOperate(*matrix, result, residual, cfg.matrix_width);
        VectorSub(*rhs, residual, residual);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        k++;
    }

    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
    LOG_INFO_CLI("SimpleIter finished");
    std::cout << "Iterations total: " << k << " Elapsed time: " << duration << " Residual 2-norm: " << curr_tol << '\n';

    return result;
}