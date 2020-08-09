#ifndef GD_OPERATION_COPY_H
#define GD_OPERATION_COPY_H

#include "buffer/simple_buffer.h"

#include <xmmintrin.h>

namespace gd
{
template<typename T, unsigned int Alignment>
void copy(buffer::SimpleBuffer<T, Alignment>& dst,
          const buffer::SimpleBuffer<T, Alignment>& src)
{
    const size_t N = dst.xsize() * dst.ysize();
    for (size_t z = 0; z < dst.zsize(); ++z)
    {
        T* arr_dst = dst(z);
        const T* arr_src = src(z);
        for (size_t n = 0; n < N; ++n)
        {
            arr_dst[n] = arr_src[n];
        }
    }
}

namespace m128
{
template<unsigned int Alignment>
void copy(buffer::SimpleBuffer<float, Alignment>& dst,
          const buffer::SimpleBuffer<float, Alignment>& src)
{
    static_assert(Alignment >= 16);

    const size_t N = dst.xsize() * dst.ysize();
    for (size_t z = 0; z < dst.zsize(); ++z)
    {
        float* arr_dst = dst(z);
        const float* arr_src = src(z);
        for (size_t n = 0; n < N; n += 4)
        {
            _mm_store_ps(arr_dst + n, _mm_load_ps(arr_src + n));
        }
    }
}

} // namespace m128

} // namespace gd

#endif