// #include "core/netProcess.hpp"
// #include "core/task.hpp"
// #include "dataTypes/common.hpp"
// #include "dataTypes/config.hpp"
// #include "nm/utils/logger.hpp"
// #include "nm/utils/profiler.hpp"
// #include <cstddef>
// #include <iostream>
// #include <vector>

// static void GenLSETestFunc(const std::string& fname, nm::Profiler& prof) {
//     nm::Profiler nest = prof.nest(nm::GET_CURRENT_SCOPE());
//     NetPattern pat = ImportNetPattern(fname);
//     LOG_INFO_CLI("Got pattern");
//     size_t n = 100;
//     Net net = pat.generateNet(n, 0, 0, 1.l / n, 1.l / n);

//     LOG_INFO_CLI("Net generated");

    // for (size_t j = 0; j < net.nodes[0].size(); ++j) {
    //     for (size_t i = 0; i < net.nodes.size(); ++i) {
    //         if (net.nodes[i][j] == NodeType::BOUND) {
    //             std::cout << 'o';
    //         } else if (net.nodes[i][j] == NodeType::INNER) {
    //             std::cout << 'x';
    //         } else {
    //             std::cout << ' ';
    //         }
    //     }
    //     std::cout << '\n';
    // }
//     auto fb = [](const double& x, const double& y) -> double {
//         return (x + y);
//     };
//     auto fr = [](const double& x, const double& y) -> double {
//         return 1 - x - y;
//     };

//     Config cfg;
//     cfg.startX = nm::StartApr::Zeros;

//     cfg.tolerance = 1e-4;
//     cfg.Max_N = 100000;
//     cfg.CountCutX = n;
//     cfg.CountCutY = n;

//     DirichletTask dt(fb, fr, net, cfg);

//     LOG_INFO_CLI("Genetaring LS");
//     dt.GenerateLinearSystem();
//     auto lscoefs = dt.Coefs();
//     auto lsrhs = dt.Rhs();
//     LOG_INFO_CLI("LS generated");

//     size_t width = net.nodes.size();
//     size_t height = net.nodes[0].size();

//     // std::cout << "Matrix" << '\n';

//     // std::cout << lscoefs[0] << ' ';
//     // size_t k = 0;
//     // for (size_t i = 1; i < lscoefs.size(); ++i) {
//     //     if (i % 5 == 0) {
//     //         std::cout << "| " << lsrhs[k];
//     //         k++;
//     //         std::cout << '\n';
//     //     }
//     //     std::cout << lscoefs[i] << ' ';
//     // }
//     // std::cout << "| " << lsrhs[k];
//     // std::cout << '\n';

//     std::cout << "Var vector size: " << dt.Rhs().size() << '\n';

//     dt.SetMethod(nm::Method::CGM);
//     LOG_INFO_CLI("Evaluating tasak...");
//     dt.eval();
//     LOG_INFO_CLI("Task evaluated");
//     std::vector<double> sol1(dt.Solution().size());
//     sol1 = dt.Solution();

//     std::cout << "CGM solution\n";
//     for (size_t i = 0; i < 10; ++i) {
//         std::cout << dt.Solution()[i] << '\n';
//     }

//     dt.SetMethod(nm::Method::SimpleIter);
//     dt.eval();

//     std::vector<double> sol2(dt.Solution().size());
//     sol2 = dt.Solution();

//     std::cout << "SIM solution\n";
//     for (size_t i = 0; i < 10; ++i) {
//         std::cout << dt.Solution()[i] << '\n';
//     }

//     dt.SetMethod(nm::Method::SOR);
//     dt.eval();

//     std::vector<double> sol3(dt.Solution().size());
//     sol3 = dt.Solution();

//     std::cout << "SOR solution\n";
//     for (size_t i = 0; i < 10; ++i) {
//         std::cout << dt.Solution()[i] << '\n';
//     }

//     double diff = 0.l;
//     double curr_diff = 0.l;
//     for (size_t i = 0; i < sol1.size(); ++i) {
//         curr_diff = std::abs(sol1[i] - sol2[i]);
//         if (curr_diff > diff)
//             diff = curr_diff;
//     }

//     std::cout << "Diff betw CGM and SIM: " << diff << '\n';
//     for (size_t i = 0; i < sol3.size(); ++i) {
//         curr_diff = std::abs(sol1[i] - sol3[i]);
//         if (curr_diff > diff)
//             diff = curr_diff;
//     }

//     std::cout << "Diff betw CGM and SOR: " << diff << '\n';
// }


 int main(int argc, char* argv[]) {
//     nm::Profiler prof;
//     GenLSETestFunc(argv[1], prof);
     return 0;
 }
