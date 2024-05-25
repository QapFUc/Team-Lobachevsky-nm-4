#include "core/SimpleIter.hpp"
#include <vector>

SimpleIter::SimpleIter(std::vector<double> m, std::vector<double> rhs, SimpleIterMethodConfig config )
    : MethodInterface(std::move(m), std::move(rhs), std::move(config)) {}

std::vector<double> SimpleIter::eval() {
    std::vector<double> result(config.startX.size());
    auto X = config.startX;
    double Parametr = 1/(-2*matrix[2]+4);
    int n = 0;
    double resist = 100;
    while (n < config.Max_N && resist < config.tolerance) {
        resist = 0;
        result[0] = X[0] - Parametr * ((matrix[0 * 5 + 2] * X[0] + matrix[0 * 5 + 3] * X[1] + matrix[0 * 5 + 4] * X[4]) - rhs[0]);
        result[1] = X[1] - Parametr * ((matrix[1 * 5 + 1] * X[0] + matrix[1 * 5 + 2] * X[1] + matrix[1 * 5 + 3] * X[2] + matrix[1 * 5 + 4] * X[5]) - rhs[1]);
        result[2] = X[2] - Parametr * ((matrix[2 * 5 + 1] * X[1] + matrix[2 * 5 + 2] * X[2] + matrix[2 * 5 + 3] * X[3] + matrix[2 * 5 + 4] * X[6]) - rhs[2]);
        result[3] = X[3] - Parametr * ((matrix[3 * 5 + 1] * X[2] + matrix[3 * 5 + 2] * X[3] + matrix[3 * 5 + 3] * X[4] + matrix[3 * 5 + 4] * X[7]) - rhs[3]);
        for (int i = 4; i < rhs.size() - 4; ++i) {
            result[i] = X[i] - Parametr * ((matrix[i * 5 + 0] * X[i - 4] + matrix[i * 5 + 1] * X[i - 1] + matrix[i * 5 + 2] * X[i] +
                                            matrix[i * 5 + 3] * X[i + 1] + matrix[i * 5 + 4] * X[i + 4]) -
                                           rhs[i]);
        }
        result[rhs.size() - 4] =
            X[rhs.size() - 4] -
            Parametr * ((matrix[(rhs.size() - 4) * 5 + 0] * X[(rhs.size() - 4) - 4] + matrix[(rhs.size() - 4) * 5 + 1] * X[(rhs.size() - 4) - 1] +
                         matrix[(rhs.size() - 4) * 5 + 2] * X[rhs.size() - 4] + matrix[(rhs.size() - 4) * 5 + 3] * X[(rhs.size() - 4) + 1]) -
                        rhs[rhs.size() - 4]);
        result[rhs.size() - 3] =
            X[rhs.size() - 3] -
            Parametr * ((matrix[(rhs.size() - 3) * 5 + 0] * X[(rhs.size() - 3) - 4] + matrix[(rhs.size() - 3) * 5 + 1] * X[(rhs.size() - 3) - 1] +
                         matrix[(rhs.size() - 3) * 5 + 2] * X[rhs.size() - 3] + matrix[(rhs.size() - 3) * 5 + 3] * X[(rhs.size() - 3) + 1]) -
                        rhs[rhs.size() - 3]);
        result[rhs.size() - 2] =
            X[rhs.size() - 2] -
            Parametr * ((matrix[(rhs.size() - 2) * 5 + 0] * X[(rhs.size() - 2) - 4] + matrix[(rhs.size() - 2) * 5 + 1] * X[(rhs.size() - 2) - 1] +
                         matrix[(rhs.size() - 2) * 5 + 2] * X[rhs.size() - 2] + matrix[(rhs.size() - 2) * 5 + 3] * X[(rhs.size() - 2) + 1]) -
                        rhs[rhs.size() - 2]);
        result[rhs.size() - 1] = X[rhs.size() - 1] - Parametr * ((matrix[(rhs.size() - 1) * 5 + 0] * X[(rhs.size() - 1) - 4] +
                                                                  matrix[(rhs.size() - 1) * 5 + 1] * X[(rhs.size() - 1) - 1] +
                                                                  matrix[(rhs.size() - 1) * 5 + 2] * X[rhs.size() - 1]) -
                                                                 rhs[rhs.size() - 1]);
        X = result;
        for(int i=0;i<config.startX.size();++i){
            if (std::abs(rhs[i]-X[i])>resist) {resist=std::abs(rhs[i]-X[i]);}
        }
        n++;
    }
    return X;
}