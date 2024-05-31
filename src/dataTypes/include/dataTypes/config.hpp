#pragma once

#include "dataTypes/common.hpp"
#include <cstddef>
#include <vector>
#ifndef CONFIG_HPP
#    define CONFIG_HPP

struct MethodConfig {
    nm::StartApr startX;
    double tolerance;
    std::vector<size_t> net_widthes;
    size_t Max_N = 0;
    size_t n;
    size_t m;
};

struct SORconfig:MethodConfig{
    double omega;
};

struct SimpleIterMethodConfig : MethodConfig {};

struct Config {
    double StartXArea = .0;
    double EndXArea = .0;
    double StartYArea = .0;
    double EndYArea = .0;
    double CountCutX = .0;
    double CountCutY = .0;
    double Accuracy = 1.0;
    size_t Max_N = 0;
    size_t Parametr = 0;
    int Task = 0;
    nm::StartApr startX;
    double tolerance;
    Config(const double StartXArea,
           const double EndXArea,
           const double StartYArea,
           const double EndYArea,
           const double& CountCutX,
           const double& CountCutY,
           const size_t& Max_N,
           const int& Task,
           const size_t& Parametr,
           const nm::StartApr& startX,
           const double& tolerance)
        : StartXArea(StartXArea), EndXArea(EndXArea), StartYArea(StartYArea), EndYArea(EndYArea), CountCutX(CountCutX), CountCutY(CountCutY), Max_N(Max_N),
          Task(Task), Parametr(Parametr), startX(startX), tolerance(tolerance) {}
    Config() = default;
};

struct ExitConfig {
    size_t Iterations;
    std::vector<double> solution;
    std::vector<double> prevsol;
    double N;
    double Parametr = 0;
    double tolerance;
    double MaxDistance;
    double xMaxDistance;
    double yMaxDistance;
};
#endif