#pragma once

#include "core/methods.hpp"
#include "dataTypes/config.hpp"

class SuccessiveOverRelax : public MethodInterface {
public:
    SuccessiveOverRelax() = default;
    SuccessiveOverRelax(const std::vector<double>* m, const std::vector<double>* rhs, const SORconfig& cfg) : MethodInterface(m, rhs, cfg), cfg(cfg) {}
    ~SuccessiveOverRelax() override {}

    std::vector<double> eval() override;

private:

    SORconfig cfg;
};