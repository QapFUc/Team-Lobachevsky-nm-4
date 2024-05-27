#include "core/netProcess.hpp"
#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include "nm/utils/logger.hpp"
#include "nm/utils/profiler.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

static void GenLSETestFunc(const std::string& fname, nm::Profiler& prof) {
    nm::Profiler nest = prof.nest(nm::GET_CURRENT_SCOPE());
    NetPattern pat = ImportNetPattern(fname);
    LOG_INFO_CLI("Got pattern");
    Net net = pat.generateNet(5000, 0, 0, 0.1, 0.1);

    LOG_INFO_CLI("Net generated");

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
    auto fb = [](const double& x, const double& y) -> double {
        return (x + y);
    };
    auto fr = [](const double& x, const double& y) -> double {
        return 1 - x - y;
    };

    Config cfg;
    cfg.startX = nm::StartApr::Zeros;
    cfg.tolerance = 1e-7;
    cfg.Max_N = 100000;

    DirichletTask dt(fb, fr, net, cfg);

    LOG_INFO_CLI("Genetaring LS");
    dt.GenerateLinearSystem();
    auto lscoefs = dt.Coefs();
    auto lsrhs = dt.Rhs();
    LOG_INFO_CLI("LS generated");

    size_t width = net.nodes.size();
    size_t height = net.nodes[0].size();

    // std::cout << "Matrix" << '\n';

    // std::cout << lscoefs[0] << ' ';
    // size_t k = 0;
    // for (size_t i = 1; i < lscoefs.size(); ++i) {
    //     if (i % 5 == 0) {
    //         std::cout << "| " << lsrhs[k];
    //         k++;
    //         std::cout << '\n';
    //     }
    //     std::cout << lscoefs[i] << ' ';
    // }
    // std::cout << "| " << lsrhs[k];
    // std::cout << '\n';

    std::cout << "Var vector size: " << dt.Rhs().size() << '\n';

    dt.SetMethod(nm::Method::CGM);
    LOG_INFO_CLI("Evaluating tasak...");
    dt.eval();
    LOG_INFO_CLI("Task evaluated");
    // std::vector<double> sol1(dt.Solution().size());
    // sol1 = dt.Solution();

    std::cout << "CGM solution\n";
    for (size_t i = 0; i < 100; ++i) {
        std::cout << dt.Solution()[i] << '\n';
    }

    // dt.SetMethod(nm::Method::SimpleIter);
    // dt.eval();

    // std::vector<double> sol2(dt.Solution().size());
    // sol2 = dt.Solution();

    // std::cout << "SIM solution\n";
    // for (auto& x : sol2) {
    //     std::cout << x << '\n';
    // }

    // double diff = 0.l;
    // double curr_diff = 0.l;
    // for (size_t i = 0; i < sol1.size(); ++i) {
    //     curr_diff = std::abs(sol1[i] - sol2[i]);
    //     if (curr_diff > diff)
    //         diff = curr_diff;
    // }

    // std::cout << "Diff betw CGM and SIM: " << diff << '\n';
}

int main(int argc, char* argv[]) {
    nm::Profiler prof;
    GenLSETestFunc(argv[1], prof);
    return 0;
}
