#include "buffer/simple_buffer.h"
#include "operation/copy.h"
#include "operation/fill.h"

#include <catch.hpp>

TEMPLATE_TEST_CASE("gd::copy() is correct on SimpleBuffer<float,*>",
                   "[buffer]",
                   gd::buffer::SimpleBuffer<float>,
                   gd::buffer::m128::SimpleBuffer<float>)
{
    TestType src(256, 256, 8);
    TestType dst(256, 256, 8);
    gd::fill(src, 3.5f);
    gd::copy(dst, src);

    for (size_t z = 0; z < 8; ++z)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            for (size_t x = 0; x < 256; ++x)
            {
                REQUIRE(dst(z, y, x) == 3.5f);
            }
        }
    }
}

TEMPLATE_TEST_CASE("gd::m128::copy() is correct on SimpleBuffer<float,*>",
                   "[buffer]",
                   gd::buffer::m128::SimpleBuffer<float>)
{
    TestType src(256, 256, 8);
    TestType dst(256, 256, 8);
    gd::m128::fill(src, 3.5f);
    gd::m128::copy(dst, src);

    for (size_t z = 0; z < 8; ++z)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            for (size_t x = 0; x < 256; ++x)
            {
                REQUIRE(dst(z, y, x) == 3.5f);
            }
        }
    }
}