#include "core/CGM.hpp"
#include "core/SOR.hpp"
#include "core/SimpleIter.hpp"
#include "core/netProcess.hpp"

#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include <cstddef>
#include <iostream>
#include <vector>

void DirichletTask::GenerateLinearSystem() {
    std::vector<double> matrix;
    std::vector<double> rhsv;
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
                        rhs += -fBoundary(net.x_start + net.step_x * i, net.y_start + net.step_y * (j - 1),cfg) * invsqK;
                    }
                } else {
                    row[0] = 0;
                }

                if (i - 1 >= 0) {
                    if (net.nodes[i - 1][j] == NodeType::INNER) {
                        row[1] = invsqH;
                    } else if (net.nodes[i - 1][j] == NodeType::BOUND) {
                        row[1] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * (i - 1), net.y_start + net.step_y * j,cfg) * invsqH;
                    }
                } else {
                    row[1] = 0;
                }

                if (i + 1 < width) {
                    if (net.nodes[i + 1][j] == NodeType::INNER) {
                        row[3] = invsqH;
                    } else if (net.nodes[i + 1][j] == NodeType::BOUND) {
                        row[3] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * (i + 1), net.y_start + net.step_y * j,cfg) * invsqH;
                    }
                } else {
                    row[3] = 0;
                }

                if (j + 1 < height) {
                    if (net.nodes[i][j + 1] == NodeType::INNER) {
                        row[4] = invsqK;
                    } else if (net.nodes[i][j + 1] == NodeType::BOUND) {
                        row[4] = 0;
                        rhs += -fBoundary(net.x_start + net.step_x * i, net.y_start + net.step_y * (j + 1),cfg) * invsqK;
                    }
                } else {
                    row[4] = 0;
                }

                row[2] = -2 * (invsqH + invsqK);
                matrix.insert(matrix.end(), row.begin(), row.end());
                rhsv.push_back(rhs);
            }
        }

        lsmatrix = matrix;
        lsrhs = rhsv;
    }
}

void DirichletTask::SetMethod(const nm::Method& m) {
    if (method != nullptr) {
        delete this->method;
    }

    if (m == nm::Method::CGM) {
        MethodConfig mcfg;
        mcfg.startX = cfg.startX;
        mcfg.matrix_width = net.nodes.size();
        mcfg.tolerance = cfg.tolerance;
        mcfg.Max_N = cfg.Max_N;
        this->method = new ConjGradMethod(&lsmatrix, &lsrhs, mcfg);
    } else if (m == nm::Method::SimpleIter) {
        SimpleIterMethodConfig scfg;
        scfg.startX = cfg.startX;
        scfg.matrix_width = net.nodes.size();
        scfg.tolerance = cfg.tolerance;
        scfg.Max_N = cfg.Max_N;
        this->method = new SimpleIter(&lsmatrix, &lsrhs, scfg);
    } else if (m == nm::Method::SOR) {
        MethodConfig mcfg;
        mcfg.startX = cfg.startX;
        mcfg.matrix_width = net.nodes.size();
        mcfg.tolerance = cfg.tolerance;
        mcfg.Max_N = cfg.Max_N;
        mcfg.n = cfg.CountCutX;
        mcfg.m = cfg.CountCutY;
        this->method = new SuccessiveOverRelax(&lsmatrix, &lsrhs, mcfg);
    }
}

void DirichletTask::eval() {
    solution = this->method->eval();
}