#include "core/SimpleIter.hpp"
#include "core/vector.hpp"
#include "dataTypes/common.hpp"
#include "nm/utils/logger.hpp"
#include <cmath>
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
    MatrixOperate(*matrix, result, residual, cfg.net_widthes);
    VectorSub(*rhs, residual, residual);

    // start direction
    double curr_tol = std::sqrt(EuclidianNormSq(residual));
    double method_curr_tol = 1e10;
    size_t k = 0;

    LOG_INFO_CLI("Iterating SimpleIter...");
    std::clock_t start;
    double duration = 0.l;
    double lambda1 = (4.l * (*matrix)[3])*std::pow(std::sin(M_PI/(2*config.n)),2)+ (4.l * (*matrix)[4])*std::pow(std::sin(M_PI/(2*config.m)),2);
    double lambdan = (4.l * (*matrix)[3])*std::pow(std::sin((M_PI*(config.n-1))/(2*config.n)),2)+ (4.l * (*matrix)[4])*std::pow(std::sin((M_PI*(config.m-1))/(2*(config.m))),2);
    double parametr = -2.l/(lambda1+lambdan);
    std::cout<<parametr<<" = parametr "<<lambda1<<"< >"<<lambdan<<"  >"<< config.n<<" >" <<config.m<<std::endl;
    start = std::clock();
    while (method_curr_tol >= cfg.tolerance && k < cfg.Max_N) {
        exCfg.prevsol=result;
        VectorSum(result, residual, result, 1.l, parametr);
        MatrixOperate(*matrix, result, residual, cfg.net_widthes);
        VectorSub(*rhs, residual, residual);
        method_curr_tol = InfNormVector(exCfg.prevsol,result);
        curr_tol = std::sqrt(EuclidianNormSq(residual));
        k++;
    }
    exCfg.solution=result;
    exCfg.N=k;
    exCfg.tolerance=curr_tol;
    exCfg.Methodtolerance=method_curr_tol;
    exCfg.Parametr=parametr;
    duration = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC;
    LOG_INFO_CLI("SimpleIter finished");
    std::cout << "Iterations total: " << k << " Elapsed time: " << duration << " Residual 2-norm: " << curr_tol << '\n';

    return result;
}