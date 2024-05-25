#pragma once

#include "core/methods.hpp"
#include "dataTypes/config.hpp"

class ConjGradMethod final : public MethodInterface {
public:
    ConjGradMethod() = default;
    ConjGradMethod(std::vector<double> m, std::vector<double> rhs, const MethodConfig& cfg) : MethodInterface(m, rhs, cfg) {}

    std::vector<double> eval() override;
};