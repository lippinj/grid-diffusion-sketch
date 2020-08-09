#ifndef GD_OPERATION_FILL_H
#define GD_OPERATION_FILL_H

#include "buffer/simple_buffer.h"

#include <xmmintrin.h>

namespace gd
{
template<typename T, unsigned int Alignment>
void fill(buffer::SimpleBuffer<T, Alignment>& buffer, const T value = (T)0)
{
    const size_t N = buffer.xsize() * buffer.ysize();
    for (size_t z = 0; z < buffer.zsize(); ++z)
    {
        T* arr = buffer(z);
        for (size_t n = 0; n < N; ++n)
        {
            arr[n] = value;
        }
    }
}

namespace m128
{
template<unsigned int Alignment>
void fill(buffer::SimpleBuffer<float, Alignment>& buffer,
          const float value = 0.0)
{
    const size_t N = buffer.xsize() * buffer.ysize();
    __m128 value4 = _mm_setr_ps(value, value, value, value);

    for (size_t z = 0; z < buffer.zsize(); ++z)
    {
        float* arr = buffer(z);
        for (size_t n = 0; n < N; n += 4)
        {
            _mm_store_ps(arr + n, value4);
        }
    }
}

} // namespace m128

} // namespace gd

#endif