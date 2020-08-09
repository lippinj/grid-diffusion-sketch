#ifndef GD_OPERATION_EXCHANGE_HEAT_H
#define GD_OPERATION_EXCHANGE_HEAT_H

#include "types.h"

#include <xmmintrin.h>

namespace gd
{
template<typename T>
inline PairwiseOp<T> exchangeHeat(const T coefficient)
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

namespace m128
{
inline PairwiseOp<float> exchangeHeat(const float k)
{
    return [=](float* dst_a,
               float* dst_b,
               const float* src_a,
               const float* src_b,
               size_t N) {
        const __m128 multiplier = _mm_setr_ps(k, k, k, k);

        for (size_t n = 0; n < N; n += 4)
        {
            const __m128 A = _mm_load_ps(src_a + n);
            const __m128 B = _mm_load_ps(src_b + n);
            const __m128 amt = _mm_mul_ps(_mm_sub_ps(B, A), multiplier);
            const __m128 a = _mm_load_ps(dst_a + n);
            const __m128 b = _mm_load_ps(dst_b + n);
            _mm_store_ps(dst_a + n, _mm_add_ps(a, amt));
            _mm_store_ps(dst_b + n, _mm_sub_ps(b, amt));
        }
    };
}

} // namespace m128

} // namespace gd

#endif