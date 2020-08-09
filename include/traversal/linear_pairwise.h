#ifndef GD_TRAVERSAL_LINEAR_PAIRWISE_H
#define GD_TRAVERSAL_LINEAR_PAIRWISE_H

#include "buffer/simple_buffer.h"
#include "operation/types.h"

namespace gd
{
namespace traversal
{
template<typename T, unsigned int Alignment>
void linearPairwiseZ(buffer::SimpleBuffer<T, Alignment>& dst,
                     const buffer::SimpleBuffer<T, Alignment>& src,
                     size_t z,
                     PairwiseOp<T> op)
{
    // Operate on every pair
    //  (i,     j, z)
    //  (i + 1, j, z)
    // where
    //   i = 0 .. Nx - 2
    //   j = 0 .. Ny - 1
    for (size_t y = 0; y < src.ysize(); ++y)
    {
        op(dst(z, y), dst(z, y) + 1, src(z, y), src(z, y) + 1, src.xsize() - 1);
    }

    // Operate on every pair
    //  (i, j,     z)
    //  (i, j + 1, z)
    // where
    //   i = 0 .. Nx - 1
    //   j = 0 .. Ny - 2
    for (size_t y = 0; y < (src.ysize() - 1); ++y)
    {
        op(dst(z, y), dst(z, y + 1), src(z, y), src(z, y + 1), src.xsize());
    }

    // Operate on every pair
    //  (i, j, z)
    //  (i, j, z + 1)
    // where
    //   i = 0 .. Nx - 1
    //   j = 0 .. Ny - 1
    if ((z + 1) < src.zsize())
    {
        op(dst(z), dst(z + 1), src(z), src(z + 1), src.xsize() * src.ysize());
    }
}

template<typename T, unsigned int Alignment>
void linearPairwise(buffer::SimpleBuffer<T, Alignment>& dst,
                    const buffer::SimpleBuffer<T, Alignment>& src,
                    PairwiseOp<T> op)
{
    for (size_t z = 0; z < src.zsize(); ++z)
    {
        linearPairwiseZ(dst, src, z, op);
    }
}

} // namespace traversal
} // namespace gd

#endif