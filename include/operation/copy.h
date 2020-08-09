#ifndef GD_OPERATION_COPY_H
#define GD_OPERATION_COPY_H

#include "buffer/simple_buffer.h"

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

} // namespace gd

#endif