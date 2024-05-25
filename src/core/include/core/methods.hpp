#pragma once

#include <vector>

class MethodInterface {
    std::vector<double> matrix;
    std::vector<double> rhs;
    std::vector<double> var;
public:
    MethodInterface();
    MethodInterface(std::vector<double> m, std::vector<double> rhs);

    virtual std::vector<double> eval();
};