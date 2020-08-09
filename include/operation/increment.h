#ifndef GD_OPERATION_INCREMENT_H
#define GD_OPERATION_INCREMENT_H

#include "types.h"

namespace gd
{
template<typename T>
PairwiseOp<T> increment()
{
    return [](T* a_dst, T* b_dst, const T*, const T*, size_t count) {
        for (size_t i = 0; i < count; ++i)
        {
            a_dst[i]++;
            b_dst[i]++;
        }
    };
}

} // namespace gd

#endif