#pragma once

#ifndef SIMPLEITER_HPP
#    define SIMPLEITER_HPP

#    include "core/methods.hpp"
#    include "core/task.hpp"
#    include "dataTypes/config.hpp"

class SimpleIter : public MethodInterface {
    SimpleIterMethodConfig config;
public:
    SimpleIter() = default;
    SimpleIter(std::vector<double> m, std::vector<double> rhs, SimpleIterMethodConfig config);
    std::vector<double> eval() override;
};

#endif // SIMPLEITER_HPP