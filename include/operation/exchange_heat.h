#ifndef GD_OPERATION_EXCHANGE_HEAT_H
#define GD_OPERATION_EXCHANGE_HEAT_H

#include "types.h"

namespace gd
{
template<typename T>
PairwiseOp<T> exchangeHeat(const T coefficient)
{
    return
        [=](T* dst_a, T* dst_b, const T* src_a, const T* src_b, size_t count) {
            for (size_t i = 0; i < count; ++i)
            {
                const T exchanged_amount = coefficient * (src_b[i] - src_a[i]);
                dst_a[i] += exchanged_amount;
                dst_b[i] -= exchanged_amount;
            }
        };
}

} // namespace gd

#endif