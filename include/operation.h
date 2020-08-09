#ifndef GD_OPERATION_H
#define GD_OPERATION_H

#include <functional>

template<typename T>
using LineOperation = std::function<void(T*, T*, const T*, const T*, size_t)>;

template<typename T>
LineOperation<T> increment()
{
    return
        [=](T* dst_a, T* dst_b, const T*, const T*, size_t count) {
            for (size_t i = 0; i < count; ++i)
            {
                (*dst_a)++;
                (*dst_b)++;
                dst_a++;
                dst_b++;
            }
        };
}

template<typename T>
LineOperation<T> heatTransfer(const T coefficient)
{
    return
        [=](T* dst_a, T* dst_b, const T* src_a, const T* src_b, size_t count) {
            for (size_t i = 0; i < count; ++i)
            {
                const T amount = coefficient * (src_b - src_a);
                *dst_a += amount;
                *dst_b -= amount;
                dst_a++;
                dst_b++;
                src_a++;
                src_b++;
            }
        };
}

#endif