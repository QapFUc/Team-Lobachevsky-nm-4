#include "core/SimpleIter.hpp"
#include "core/vector.hpp"
#include "dataTypes/common.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include "nm/utils/logger.hpp"


std::vector<double> SimpleIter::eval() {
    LOG_INFO_CLI("Creating vectors");
    std::vector<double> result(rhs->size());
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
    double curr_tol = 1e15;
    size_t k = 0;
    double percentage = 0.l;
    double perc_step = (1.l / cfg.Max_N);
    std::vector<double> tmp(rhs->size());
    LOG_INFO_CLI("Iterating SimpleIter...");
    std::cout << percentage * 100.l << "\% done ";
    std::clock_t start;
    double duration = 0.l;
    double lambda_min = 1e15;
    double lambda_max = -1e15;
    for (int i = 0; i<5*rhs->size();i=i+5) {
        double tmp = std::abs((*matrix)[i])+std::abs((*matrix)[i+1])+std::abs((*matrix)[i+3])+std::abs((*matrix)[i+4]);
        if ((*matrix)[i+2]-tmp <lambda_min) {lambda_min = (*matrix)[i+2]-tmp ;}
        if ((*matrix)[i+2]+tmp >lambda_max) {lambda_max = (*matrix)[i+2]+tmp ;}
    }
    double parametr = (2.l/(lambda_max+lambda_min));
    while (curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        start = std::clock();
        VectorSum(result, residual, result,1.l,parametr);
        MatrixOperate(*matrix, result, residual, cfg.matrix_width);
        VectorSub(*rhs, residual, residual);
        k++;
        duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
        percentage += perc_step;
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        std::cout << '\r' << percentage * 100.l << "\% done " << ". Estimation time (approx): " << duration * (cfg.Max_N - k) << " s" <<  std::flush;
    }

    std::cout << '\n';
    std::cout << "Total tolerance: " << curr_tol << '\n';
    LOG_INFO_CLI("SimpleIter finished");
    return result;
}