#pragma once

#include <cstddef>
#ifndef CONFIG_HPP
#    define CONFIG_HPP

struct Config {
    double CountCutX = .0;
    double CountCutY = .0;
    double Accuracy = 1.0;
    size_t Max_N = 0;
    size_t Parametr = 0;
    int Task = 0;
    Config(const double& CountCutX, const double& CountCutY, const double& Accuracy,const size_t& Max_N, const int& Task, const size_t& Parametr);
    Config() = default;
};
#endif