#pragma once

#ifndef SIMPLEITER_HPP
#    define SIMPLEITER_HPP

#    include "core/methods.hpp"
#    include "core/task.hpp"
#    include "dataTypes/config.hpp"

class SimpleIter final : public MethodInterface {
    SimpleIterMethodConfig config;

public:
    SimpleIter() = default;
    SimpleIter(const std::vector<double>& m, const std::vector<double>& rhs, const SimpleIterMethodConfig& config)
        : MethodInterface(m, rhs, config), config(config) {}
    std::vector<double> eval() override;
};

#endif  // SIMPLEITER_HPP