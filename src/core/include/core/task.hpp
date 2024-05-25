#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include "core/netProcess.hpp"
#include "core/methods.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"

class DirichletTask {
    std::function<double(double, double)> fBoundary;
    std::function<double(double, double)> fRhs;
    std::vector<double> lsmatrix;
    std::vector<double> lsrhs;
    std::vector<double> solution;
    Net net;
    Config cfg;
    MethodInterface method;
public:
    DirichletTask() = default;
    DirichletTask(std::function<double(double, double)> fBoundary, std::function<double(double, double)> fRhs, const Net& net, const Config& cfg) : fBoundary(fBoundary), fRhs(fRhs), net(net), cfg(cfg) {}

    void GenerateLinearSystem();
    void SetMethod(const nm::Method& m);
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

