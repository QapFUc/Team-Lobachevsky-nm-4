#pragma once

#include <cstddef>
#include <vector>
#include "dataTypes/config.hpp"


class MethodInterface {
protected:
    const std::vector<double>* matrix;
    const std::vector<double>* rhs;
    MethodConfig cfg;
    ExitConfig exCfg;

public:
    MethodInterface() = default;
    MethodInterface( const std::vector<double>* m, const std::vector<double>* rhs, const MethodConfig& cfg)
        : matrix(m), rhs(rhs), cfg(cfg) {}
    virtual ~MethodInterface() {}

    virtual std::vector<double> eval() = 0;

    std::vector<double> InitialX() const;

    ExitConfig GetExitConfig() const {
        return exCfg;
    }
};

