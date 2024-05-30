#pragma once

#include "core/methods.hpp"
#include "core/netProcess.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include <cstddef>
#include <functional>
#include <vector>

class DirichletTask {
    std::function<double(double, double, Config)> fBoundary;  // Граничные условия все
    std::function<double(double, double)> fRhs;               // Неоднородность
    std::vector<double> lsmatrix;                             // матрица (то что осталось)
    std::vector<double> lsrhs;                                // значение функции
    std::vector<double> solution;                             // само решение готовое
    Net net;                                                  // сетка
    Config cfg;
    MethodInterface* method = nullptr;

public:
    DirichletTask() = default;
    DirichletTask(std::function<double(double, double, Config)> fBoundary, std::function<double(double, double)> fRhs, const Net& net, const Config& cfg)
        : fBoundary(fBoundary), fRhs(fRhs), net(net), cfg(cfg) {}

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

    void SetNet(const Net& net) {
        this->net = net;
    }
    void SetConfig(const Config& config) {
        this->cfg = config;
    }

    double Boundary(const double& x, const double& y) {
        return fBoundary(x, y, cfg);
    }

    void SetBoundary(std::function<double(double, double, Config)>& f) {
        fBoundary = f;
    }
    void SetRHS(std::function<double(double, double)>& f) {
        fRhs = f;
    }
};
