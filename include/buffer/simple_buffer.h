#ifndef GD_BUFFER_SIMPLE_BUFFER_H
#define GD_BUFFER_SIMPLE_BUFFER_H

#include <cstdlib>
#include <vector>

namespace gd
{
namespace buffer
{
template<typename T, unsigned int Alignment = 1>
class SimpleBuffer
{
public:
    using DataType = T;

    SimpleBuffer(size_t xsize, size_t ysize, size_t zsize)
        : xsize_(xsize), ysize_(ysize), zsize_(zsize), data_(zsize)
    {
        size_t line_size = xsize_ * ysize_ * sizeof(T);
        if constexpr (Alignment > 1)
        {
            for (auto& p : data_)
            {
                p = (T*)std::malloc(line_size);
            }
        }
        else
        {
            for (auto& p : data_)
            {
                p = (T*)std::aligned_alloc(Alignment, line_size);
            }
        }
    }

    ~SimpleBuffer()
    {
        for (auto p : data_)
        {
            std::free(p);
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

    inline T* operator()(size_t z)
    {
        return data_[z];
    }

    inline const T* operator()(size_t z) const
    {
        return data_[z];
    }

    inline T* operator()(size_t z, size_t y)
    {
        return operator()(z) + (y * xsize_);
    }

    inline const T* operator()(size_t z, size_t y) const
    {
        return operator()(z) + (y * xsize_);
    }

    inline T& operator()(size_t z, size_t y, size_t x)
    {
        return operator()(z, y)[x];
    }

    inline const T& operator()(size_t z, size_t y, size_t x) const
    {
        return operator()(z, y)[x];
    }

private:
    size_t xsize_;
    size_t ysize_;
    size_t zsize_;
    std::vector<T*> data_;
};

} // namespace buffer
} // namespace gd

#endif