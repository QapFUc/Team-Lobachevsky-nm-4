#include "core/methods.hpp"
#include "dataTypes/common.hpp"
#include <vector>

std::vector<double> MethodInterface::InitialX() const {
    std::vector<double> initx(rhs->size());

    switch (cfg.startX) {
    case nm::StartApr::Zeros: {
        return initx;
    }
    }
}