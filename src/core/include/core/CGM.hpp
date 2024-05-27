#pragma once

#include "core/methods.hpp"
#include "dataTypes/config.hpp"

class ConjGradMethod final : public MethodInterface {
public:
    ConjGradMethod() = default;
    ConjGradMethod(const std::vector<double>* m, const std::vector<double>* rhs, const MethodConfig& cfg) : MethodInterface(m, rhs, cfg) {}
    ~ConjGradMethod() override {}

    std::vector<double> eval() override;
};