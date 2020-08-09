#ifndef GD_OPERATION_FILL_H
#define GD_OPERATION_FILL_H

#include "buffer/simple_buffer.h"

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

} // namespace gd

#endif