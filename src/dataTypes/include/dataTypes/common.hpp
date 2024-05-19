#pragma once

namespace nm {
namespace dtypes {
enum struct ElemType {
    uint8 = 0,
    uint32 = 1,
    uint64,
    int8 ,
    int32,
    int64,
    fp32,
    fp64
};
} // namespace dtypes

enum struct Status {
    Failure = 0,
    Success = 1
};
} // namespace nm