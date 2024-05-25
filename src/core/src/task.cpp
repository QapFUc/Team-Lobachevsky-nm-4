#include "core/CGM.hpp"
#include "core/netProcess.hpp"

#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

void DirichletTask::GenerateLinearSystem() {
    size_t width = net.nodes.size();
    size_t height = net.nodes[0].size();
    double invsqH = 1. / net.step_x;
    invsqH *= invsqH;
    double invsqK = 1. / net.step_y;
    invsqK *= invsqK;

    std::vector<double> row(5);
    for (size_t j = 0; j < height; ++j) {
        for (size_t i = 0; i < width; ++i) {
            if (net.nodes[i][j] == NodeType::INNER) {
                double rhs = -fRhs(net.x_start + net.step_x * i, net.y_start + net.step_y * j);
                if (j - 1 >= 0) {
                    if (net.nodes[i][j - 1] == NodeType::INNER) {
                        row[0] = invsqK;
                    } else if (net.nodes[i][j - 1] == NodeType::BOUND) {
                        row[0] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * i, net.y_start + net.step_y * (j - 1)) * invsqK;
                    }
                } else {
                    row[0] = 0;
                }

                if (i - 1 >= 0) {
                    if (net.nodes[i - 1][j] == NodeType::INNER) {
                        row[1] = invsqH;
                    } else if (net.nodes[i - 1][j] == NodeType::BOUND) {
                        row[1] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * (i - 1), net.y_start + net.step_y * j) * invsqH;
                    }
                } else {
                    row[1] = 0;
                }

                if (i + 1 < width) {
                    if (net.nodes[i + 1][j] == NodeType::INNER) {
                        row[3] = invsqH;
                    } else if (net.nodes[i + 1][j] == NodeType::BOUND) {
                        row[3] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * (i + 1), net.y_start + net.step_y * j) * invsqH;
                    }
                } else {
                    row[3] = 0;
                }

                if (j + 1 < height) {
                    if (net.nodes[i][j + 1] == NodeType::INNER) {
                        row[4] = invsqK;
                    } else if (net.nodes[i][j + 1] == NodeType::BOUND) {
                        row[4] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * i, net.y_start + net.step_y * (j + 1)) * invsqK;
                    }
                } else {
                    row[4] = 0;
                }

                row[2] = -2 * (invsqH + invsqK);
                lsmatrix.insert(lsmatrix.end(), row.begin(), row.end());
                lsrhs.push_back(rhs);
            }
        }
    }
}

void DirichletTask::SetMethod(const nm::Method& m) {
    MethodConfig mcfg;
    mcfg.startX = cfg.startX;
    mcfg.matrix_width = net.nodes.size();
    mcfg.tolerance = cfg.tolerance;
    
    switch (m) {
    case nm::Method::CGM:
        method = ConjGradMethod(lsmatrix, lsrhs, mcfg);
    case nm::Method::SimpleIter:
        return;
    default:
        return;
    }
}