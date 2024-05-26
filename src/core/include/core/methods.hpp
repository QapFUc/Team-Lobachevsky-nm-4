#pragma once

#include <vector>
#include "dataTypes/config.hpp"

class MethodInterface {
protected:
    std::vector<double> matrix;
    std::vector<double> rhs;
    MethodConfig cfg;

public:
    MethodInterface() = default;
    MethodInterface(const std::vector<double>& m, const std::vector<double>& rhs, const MethodConfig& cfg)
        : matrix(m), rhs(rhs), cfg(cfg) {}
    virtual ~MethodInterface() {}

    virtual std::vector<double> eval() = 0;
};