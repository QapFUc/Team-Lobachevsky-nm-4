// #include "core/CGM.hpp"
// #include <cmath>
// #include <cstddef>
// #include <numeric>
// #include <vector>

// static void MatrixOperate(const std::vector<double>& A, const std::vector<double>& x, std::vector<double> res, const size_t& width) {
//     size_t i = 0, j = 0;

//     res[0] = A[2] * x[0] + A[3] * x[1] + A[4] * x[width];
//     res[1] = A[6] * x[0] + A[7] * x[1] + A[8] * x[2] + A[9] * x[width + 1];

//     size_t k = 0;
//     for (size_t m = 2; m < x.size() - 2; ++m) {
//         k = 5 * m;
//         i = m % width;
//         if (i == 0)
//             j++;

//         res[m] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width] + A[k + 3] * x[i + 1 + j * width] +
//                  A[k + 4] * x[i + (j + 1) * width];
//     }

//     k += 5;
//     i = (x.size() - 2) % width;
//     if (i == 0)
//         j++;
//     res[x.size() - 2] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width] + A[k + 3] * x[i + 1 + j * width];
//     k += 5;
//     i = (x.size() - 1) % width;
//     if (i == 0)
//         j++;
//     res[x.size() - 1] = A[k] * x[i + (j - 1) * width] + A[k + 1] * x[i - 1 + j * width] + A[k + 2] * x[i + j * width];
// }

// static void VectorSum(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1, const double& b = 1) {
//     for (size_t k = 0; k < x.size(); ++k) {
//         res[k] = a * x[k] + b * y[k];
//     }
// }

// static void VectorSub(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& res, const double& a = 1, const double& b = 1) {
//     for (size_t k = 0; k < x.size(); ++k) {
//         res[k] = a * x[k] - b * y[k];
//     }
// }

// static double InnerProd(const std::vector<double>& x, const std::vector<double>& y) {
//     double res = 0.l;
//     for (size_t k = 0; k < x.size(); ++k) {
//         res += x[k] * y[k];
//     }
// }

// static double EuclidianNormSq(const std::vector<double>& x) { 
//     return InnerProd(x, x);
// }

// std::vector<double> MBP::eval() {
//     std::vector<double> result(rhs.size(), 0.0); 
//     double omega = 1.5; 

//     double eps = cfg.tolerance; 
//     size_t Nmax = cfg.max_iterations; 

//     std::vector<double> tmp(rhs.size());
//     double eps_cur = 0.0;
//     double eps_max = 0.0;
//     size_t k = 0;

//     while (k < Nmax) {
//         eps_max = 0.0;

//         for (size_t i = 0; i < rhs.size(); ++i) {
//             double sum = 0.0;
//             double diag = matrix[5 * i];
//             for (size_t j = 0; j < rhs.size(); ++j) {
//                 if (j != i) {
//                     sum += matrix[5 * i + j + 1] * result[j]; 
//                 }
//             }

//             double new_val = (1 - omega) * result[i] + omega * ((rhs[i] - sum) / diag); 
//             eps_cur = std::abs(result[i] - new_val);

//             if (eps_cur > eps_max) {
//                 eps_max = eps_cur;
//             }

//             result[i] = new_val;
//         }

//         if (eps_max < eps) {
//             break; 
//         }

//         k++;
//     }

//     return result;
// }