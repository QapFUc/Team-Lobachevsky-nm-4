#pragma once

#include "core/methods.hpp"

class SuccessiveOverRelax : public MethodInterface {
public:
    SuccessiveOverRelax() = default;
    SuccessiveOverRelax(const std::vector<double>* m, const std::vector<double>* rhs, const MethodConfig& cfg) : MethodInterface(m, rhs, cfg) {}
    ~SuccessiveOverRelax() override {}

    std::vector<double> eval() override;
};