#pragma once

#include <cstddef>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

enum struct NodeType {
    OUT = -1,
    INNER = 0,
    BOUND = 1,
};

struct Node {
    size_t i = 0;
    size_t j = 0;
    NodeType type = NodeType::INNER;
};

struct Net {
    std::vector<std::vector<NodeType>> nodes;
    double x_start;
    double y_start;
    double step_x;
    double step_y;

    Net();
    Net(const double& x_0, const double& y_0, const double& stepx, const double& stepy) : x_start(x_0), y_start(y_0), step_x(stepx), step_y(stepy) {}
};

struct CheckFunction {
    std::function<NodeType(size_t, size_t, double, double, double, double)> checkf;
    double x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    NodeType operator()(const size_t& i, const size_t& j) {
        return checkf(i, j, x1, x2, y1, y2);
    }
};

class NetPattern {
    size_t n = 0;
    double width_mul = 0.l;
    std::vector<CheckFunction> checkFs;

    NodeType checkNodeType(const size_t& i, const size_t& j);

public:
    NetPattern() = default;
    NetPattern(const double& width_mul) : width_mul(width_mul) {}

    void setMainSpace(const double& width_mul) {
        this->width_mul = width_mul;
    }
    void addEmptySpace(const double& x1, const double& x2, const double& y1, const double& y2);

    Net generateNet(const size_t& n, const double& x_start, const double& y_start, const double& step_x, const double& step_y);

    static NetPattern readFromFile(std::ifstream& file);
};

NetPattern ImportNetPattern(const std::string& fname);