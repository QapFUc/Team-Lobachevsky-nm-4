#pragma once

#include <vector>

class MethodInterface {
protected:
    std::vector<double> matrix;
    std::vector<double> rhs;
    double tolerance;
public:
    MethodInterface();
    MethodInterface(std::vector<double> m, std::vector<double> rhs, const double& tolerance);

    virtual std::vector<double> eval();
};
