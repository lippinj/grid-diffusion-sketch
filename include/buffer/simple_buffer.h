#ifndef GD_BUFFER_SIMPLE_BUFFER_H
#define GD_BUFFER_SIMPLE_BUFFER_H

#include <vector>

namespace gd
{
namespace buffer
{
template<typename T, bool Aligned = false>
class SimpleBuffer
{
public:
    using DataType = T;

    SimpleBuffer(size_t xsize, size_t ysize, size_t zsize)
        : xsize_(xsize), ysize_(ysize), zsize_(zsize), data_(zsize)
    {
        for (auto& v : data_)
        {
            v.resize(xsize_ * ysize_);
        }
    }

    inline size_t xsize() const
    {
        return xsize_;
    }

    inline size_t ysize() const
    {
        return ysize_;
    }

    inline size_t zsize() const
    {
        return zsize_;
    }

    inline void fill(const T value = (T)0)
    {
        for (auto& v : data_)
        {
            std::fill(v.begin(), v.end(), value);
        }
    }

    inline T* levelBegin(size_t z)
    {
        return data_[z].data();
    }

    inline const T* levelBegin(size_t z) const
    {
        return data_[z].data();
    }

    inline T* levelEnd(size_t z)
    {
        return levelBegin(z) + (xsize_ * ysize_);
    }

    inline const T* levelEnd(size_t z) const
    {
        return levelBegin(z) + (xsize_ * ysize_);
    }

    inline T* lineBegin(size_t z, size_t y)
    {
        return levelBegin(z) + (y * xsize_);
    }

    inline const T* lineBegin(size_t z, size_t y) const
    {
        return levelBegin(z) + (y * xsize_);
    }

    inline T* lineEnd(size_t z, size_t y)
    {
        return lineBegin(z, y + 1);
    }

    inline const T* lineEnd(size_t z, size_t y) const
    {
        return lineBegin(z, y + 1);
    }

    inline T& cell(size_t x, size_t y, size_t z)
    {
        return lineBegin(z, y)[x];
    }

    inline const T& cell(size_t x, size_t y, size_t z) const
    {
        return lineBegin(z, y)[x];
    }

private:
    size_t xsize_;
    size_t ysize_;
    size_t zsize_;
    std::vector<std::vector<T>> data_;
};

} // namespace buffer
} // namespace gd

#endif