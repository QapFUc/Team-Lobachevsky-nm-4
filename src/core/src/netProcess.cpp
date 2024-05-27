#include "core/netProcess.hpp"

#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

void NetPattern::addEmptySpace(const double& _x1, const double& _x2, const double& _y1, const double& _y2) {
    auto func = [&](const size_t& i, const size_t& j, const double& x1, const double& x2, const double& y1, const double& y2) -> NodeType {
        if ((i > x1 * n) && (i < (width_mul - x2) * n) && (j > y1 * n) && (j < (1 - y2) * n))
            return NodeType::OUT;
        else if (((i == x1 * n || (i == (width_mul - x2) * n)) && (j >= y1 * n && j <= (1 - y2) * n)) ||
                 ((j == y1 * n || j == (1 - y2) * n) && (i >= x1 * n && i <= (width_mul - x2) * n)))
            return NodeType::BOUND;
        return NodeType::INNER;
    };

    CheckFunction cf;
    cf.checkf = func;
    cf.x1 = _x1;
    cf.x2 = _x2;
    cf.y1 = _y1;
    cf.y2 = _y2;
    checkFs.push_back(cf);
}

NodeType NetPattern::checkNodeType(const size_t& i, const size_t& j) {
    NodeType nt;
    bool isBound = 0;
    for (size_t k = 0; k < checkFs.size(); ++k) {
        nt = checkFs[k](i, j);
        if (nt == NodeType::OUT)
            return NodeType::OUT;
        else if (nt == NodeType::BOUND)
            isBound = 1;
    }

    if (!isBound)
        return NodeType::INNER;
    else
        return NodeType::BOUND;
}

Net NetPattern::generateNet(const size_t& n, const double& x_start, const double& y_start, const double& step_x, const double& step_y) {
    this->n = n;
    size_t width = this->n * width_mul;
    size_t height = this->n;
    std::vector<std::vector<NodeType>> nodes(width);

    for (size_t i = 0; i < width; ++i) {
        std::vector<NodeType> col(height);
        for (size_t j = 0; j < height; ++j) {
            NodeType nt = NetPattern::checkNodeType(i, j);
            if ((i == 0 || j == 0 || i == width - 1 || j == height - 1) && (nt != NodeType::OUT)) {
                col[j] = NodeType::BOUND;
            } else {
                col[j] = nt;
            }

            nodes[i] = col;
        }
    }

    Net t{ x_start, y_start, step_x, step_y };
    t.nodes = nodes;
    return t;
}

NetPattern NetPattern::readFromFile(std::ifstream& file) {
    NetPattern pattern{};
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream iss(line);
            char sym;
            iss >> sym;
            if (sym == 's') {
                double width_mul;
                iss >> width_mul;
                pattern.setMainSpace(width_mul);
            }
            if (sym == 'a') {
                double x1, x2, y1, y2;
                iss >> x1 >> x2 >> y1 >> y2;

                pattern.addEmptySpace(x1, x2, y1, y2);
            }
        }
    }
    return pattern;
}

NetPattern ImportNetPattern(const std::string& fname) {
    std::ifstream file{ fname };
    if (!file)
        throw std::runtime_error("No file to import!");

    return NetPattern::readFromFile(file);
}
