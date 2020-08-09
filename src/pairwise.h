#ifndef GD_PAIRWISE_H
#define GD_PAIRWISE_H

#include "grid.h"
#include "operation.h"

template<typename T>
void pairwiseSlab(Grid<T>& dst,
                  const Grid<T>& src,
                  size_t z,
                  LineOperation<T> f)
{
    // Operate on every pair
    //  (i,     j, z)
    //  (i + 1, j, z)
    // where
    //   i = 0 .. Nx - 2
    //   j = 0 .. Ny - 1
    for (size_t y = 0; y < src.ysize(); ++y)
    {
        f(dst.lineBegin(z, y),
          dst.lineBegin(z, y) + 1,
          src.lineBegin(z, y),
          src.lineBegin(z, y) + 1,
          src.xsize() - 1);
    }

    // Operate on every pair
    //  (i, j,     z)
    //  (i, j + 1, z)
    // where
    //   i = 0 .. Nx - 1
    //   j = 0 .. Ny - 2
    for (size_t y = 0; y < (src.ysize() - 1); ++y)
    {
        f(dst.lineBegin(z, y),
          dst.lineBegin(z, y + 1),
          src.lineBegin(z, y),
          src.lineBegin(z, y + 1),
          src.xsize());
    }

    // Operate on every pair
    //  (i, j, z)
    //  (i, j, z + 1)
    // where
    //   i = 0 .. Nx - 1
    //   j = 0 .. Ny - 1
    if ((z + 1) < src.zsize())
    {
        f(dst.levelBegin(z),
          dst.levelBegin(z + 1),
          src.levelBegin(z),
          src.levelBegin(z + 1),
          src.xsize() * src.ysize());
    }
}

template<typename T>
void pairwise(Grid<T>& dst, const Grid<T>& src, LineOperation<T> f)
{
    for (size_t z = 0; z < src.zsize(); ++z)
    {
        pairwiseSlab(dst, src, z, f);
    }
}

template<typename T>
void pairwiseParallel(Grid<T>& dst, const Grid<T>& src, LineOperation<T> f)
{
#pragma omp parallel for
    for (size_t z = 0; z < src.zsize(); z += 2)
    {
        pairwiseSlab(dst, src, z, f);
    }

#pragma omp parallel for
    for (size_t z = 1; z < src.zsize(); z += 2)
    {
        pairwiseSlab(dst, src, z, f);
    }
}

#endif
