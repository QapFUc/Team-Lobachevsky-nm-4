#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include "core/netProcess.hpp"
#include "core/methods.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"

class DirichletTask {
    std::function<double(double, double)> fBoundary; // Граничные условия все
    std::function<double(double, double)> fRhs;  // Неоднородность 
    std::vector<double> lsmatrix; // матрица (то что осталось)
    std::vector<double> lsrhs; // значение функции 
    std::vector<double> solution; // само решение готовое
    Net net; // сетка
    Config cfg; 
    MethodInterface* method = nullptr;
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

