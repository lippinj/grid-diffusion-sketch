#ifndef GD_HEAT_H
#define GD_HEAT_H

#include "grid.h"

template<typename T>
inline void heatApplyToBuffers(T* dst_a,
                               T* dst_b,
                               const T* src_a,
                               const T* src_b,
                               size_t count,
                               const T multiplier = 0.01f)
{
    for (size_t i = 0; i < count; ++i)
    {
        const T amount = multiplier * (src_b - src_a);
        *dst_a += amount;
        *dst_b -= amount;
        dst_a++;
        dst_b++;
        src_a++;
        src_b++;
    }
}

template<typename T>
void heatApplyToSlice(Grid<T>& dst, const Grid<T>& src, size_t z)
{
    const size_t Nx = src.xsize();
    const size_t Ny = src.ysize();

    std::copy(src.levelBegin(z), src.levelEnd(z), dst.levelBegin(z));

    // Process neighbors on the x axis
    for (size_t y = 0; y < Ny; ++y)
    {
        const T* src_a = src.lineBegin(z, y);
        const T* src_b = src_a + 1;
        T* dst_a = dst.lineBegin(z, y);
        T* dst_b = dst_a + 1;
        heatApplyToBuffers(dst_a, dst_b, src_a, src_b, Nx - 1);
    }

    // Process neighbors on the y axis
    for (size_t y = 0; y < (Ny - 1); ++y)
    {
        const T* src_a = src.lineBegin(z, y);
        const T* src_b = src.lineBegin(z, y + 1);
        T* dst_a = dst.lineBegin(z, y);
        T* dst_b = dst.lineBegin(z, y + 1);
        heatApplyToBuffers(dst_a, dst_b, src_a, src_b, Nx);
    }

    // Process neighbors on the z axis
    if ((z + 1) < src.zsize())
    {
        const T* src_a = src.levelBegin(z);
        const T* src_b = src.levelBegin(z + 1);
        T* dst_a = dst.levelBegin(z);
        T* dst_b = dst.levelBegin(z + 1);
        heatApplyToBuffers(dst_a, dst_b, src_a, src_b, Nx * Ny);
    }
}

template<typename T>
void heatApply(Grid<T>& dst, const Grid<T>& src)
{
    for (size_t z = 0; z < src.zsize(); ++z)
    {
        heatApplyToSlice(dst, src, z);
    }
}

template<typename T>
void heatApplyParallel(Grid<T>& dst, const Grid<T>& src)
{
#pragma omp parallel for
    for (size_t z = 0; z < src.zsize(); z += 2)
    {
        heatApplyToSlice(dst, src, z);
    }

#pragma omp parallel for
    for (size_t z = 1; z < src.zsize(); z += 2)
    {
        heatApplyToSlice(dst, src, z);
    }
}

#endif