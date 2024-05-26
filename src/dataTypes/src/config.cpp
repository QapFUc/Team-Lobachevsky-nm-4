#include "dataTypes/config.hpp"

#include <cstddef>

Config::Config(const double& CountCutX, const double& CountCutY, const double& Accuracy,const size_t& Max_N, const int& Task, const size_t& Parametr) {
    this->CountCutX = CountCutX;
    this->CountCutY = CountCutY;
    this->Accuracy = Accuracy;
    this->Max_N=Max_N;
    this->Task = Task;
    this->Parametr = Parametr;
}