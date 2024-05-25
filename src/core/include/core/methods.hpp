#pragma once

#include <vector>
#include "dataTypes/config.hpp"

class MethodInterface {
protected:
    std::vector<double> matrix;
    std::vector<double> rhs;
    MethodConfig cfg;

public:
    MethodInterface();
    MethodInterface(std::vector<double> m, std::vector<double> rhs, const MethodConfig& cfg)
        : matrix(m), rhs(rhs), cfg(cfg) {}

    virtual std::vector<double> eval();
};