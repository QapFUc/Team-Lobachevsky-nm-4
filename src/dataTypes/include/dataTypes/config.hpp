#pragma once

#include <cstddef>
#include <vector>
#ifndef CONFIG_HPP
#    define CONFIG_HPP

struct MethodConfig {
    std::vector<double> startX;
    double tolerance;
    size_t matrix_width;
};

struct Config {
    double CountCutX = .0;
    double CountCutY = .0;
    double Accuracy = 1.0;
    size_t Max_N = 0;
    size_t Parametr = 0;
    int Task = 0;
    std::vector<double> startX;
    double tolerance;
    Config(const double& CountCutX,
           const double& CountCutY,
           const double& Accuracy,
           const size_t& Max_N,
           const int& Task,
           const size_t& Parametr,
           const std::vector<double>& startX,
           const double& tolerance)
        : CountCutX(CountCutX), CountCutY(CountCutY), Accuracy(Accuracy), Max_N(Max_N), Task(Task), Parametr(Parametr), startX(startX), tolerance(tolerance) {}
    Config() = default;
};
#endif