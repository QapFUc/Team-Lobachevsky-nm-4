#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

void MatrixOperate(const std::vector<double>& A, const std::vector<double>& x, std::vector<double>& res, const std::vector<size_t>& widthes);

void VectorSum(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1.l, const double& b = 1.l);

void VectorSub(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1.l, const double& b = 1.l);

double InnerProd(const std::vector<double>& x, const std::vector<double>& y);

double EuclidianNormSq(const std::vector<double>& x);

double InfNormVector(const std::vector<double>& x,const std::vector<double>& y);