#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include "core/netProcess.hpp"
#include "core/methods.hpp"

class DirichletTask {
    std::function<double(double, double)> fBoundary;
    std::function<double(double, double)> fRhs;
    std::vector<double> lsmatrix;
    std::vector<double> lsrhs;
    std::vector<double> solution;
    Net net;
    // MethodInterface method;
public:
    DirichletTask() = default;
    DirichletTask(std::function<double(double, double)> fBoundary, std::function<double(double, double)> fRhs, const Net& net) : fBoundary(fBoundary), fRhs(fRhs), net(net) {}

    void GenerateLinearSystem();
    void eval();

    std::vector<double>& Solution() {
        return solution;
    }

    std::vector<double>& Coefs() {
        return lsmatrix;
    }

    std::vector<double>& Rhs() {
        return lsrhs;
    }
};

void GenLSETestFunc(const std::string& fname);

