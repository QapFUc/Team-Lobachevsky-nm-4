#include <cstddef>
#include <iostream>
#include "dataTypes/include/dataTypes/config.hpp"
#include "nm/utils/profiler.hpp"
#include "nm/utils/logger.hpp"
#include "core/netProcess.hpp"
#include "core/task.hpp"


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

    DirichletTask dt(fb, fr, net);

    dt.GenerateLinearSystem();
    auto lscoefs = dt.Coefs();
    auto lsrhs = dt.Rhs();

    size_t width = net.nodes.size();
    size_t height = net.nodes[0].size();

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
}

int main(int argc, char* argv[]) {
	// NPTestFunc(argv[1]);
	GenLSETestFunc(argv[1]);
	return 0;
}
