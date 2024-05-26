#include "core/netProcess.hpp"
#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include "nm/utils/logger.hpp"
#include "nm/utils/profiler.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

static void GenLSETestFunc(const std::string& fname) {
    NetPattern pat = ImportNetPattern(fname);
    Net net = pat.generateNet(10, 0, 0, 0.1, 0.1);

    for (size_t j = 0; j < net.nodes[0].size(); ++j) {
        for (size_t i = 0; i < net.nodes.size(); ++i) {
            if (net.nodes[i][j] == NodeType::BOUND) {
                std::cout << 'o';
            } else if (net.nodes[i][j] == NodeType::INNER) {
                std::cout << 'x';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    auto fb = [](const double& x, const double& y) -> double {
        return (x + y);
    };
    auto fr = [](const double& x, const double& y) -> double {
        return 1 - x - y;
    };

    Config cfg;
    cfg.startX = nm::StartApr::Zeros;
    cfg.tolerance = 1e-6;
    cfg.Max_N = 10000;

    DirichletTask dt(fb, fr, net, cfg);

    dt.GenerateLinearSystem();
    auto lscoefs = dt.Coefs();
    auto lsrhs = dt.Rhs();

    size_t width = net.nodes.size();
    size_t height = net.nodes[0].size();

    std::cout << "Matrix" << '\n';

    std::cout << lscoefs[0] << ' ';
    size_t k = 0;
    for (size_t i = 1; i < lscoefs.size(); ++i) {
        if (i % 5 == 0) {
            std::cout << "| " << lsrhs[k];
            k++;
            std::cout << '\n';
        }
        std::cout << lscoefs[i] << ' ';
    }
    std::cout << "| " << lsrhs[k];
    std::cout << '\n';

    dt.SetMethod(nm::Method::CGM);
    dt.eval();
    std::vector<double> sol1(dt.Solution().size());
    sol1 = dt.Solution();

    std::cout << "CGM solution\n";
    for (auto& x : sol1) {
        std::cout << x << '\n';
    }

    dt.SetMethod(nm::Method::SimpleIter);
    dt.eval();

    std::vector<double> sol2(dt.Solution().size());
    sol2 = dt.Solution();

    std::cout << "SIM solution\n";
    for (auto& x : sol2) {
        std::cout << x << '\n';
    }

    double diff = 0.l;
    double curr_diff = 0.l;
    for (size_t i = 0; i < sol1.size(); ++i) {
        curr_diff = std::abs(sol1[i] - sol2[i]);
        if (curr_diff > diff)
            diff = curr_diff;
    }

    std::cout << "Diff betw CGM and SIM: " << diff << '\n';
}

int main(int argc, char* argv[]) {
    GenLSETestFunc(argv[1]);
    return 0;
}
