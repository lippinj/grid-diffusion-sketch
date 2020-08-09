#ifndef GD_OPERATION_TYPES_H
#define GD_OPERATION_TYPES_H

#include <functional>

namespace gd
{
template<typename T>
using PairwiseOp = std::function<void(T*, T*, const T*, const T*, size_t)>;

}

#endif