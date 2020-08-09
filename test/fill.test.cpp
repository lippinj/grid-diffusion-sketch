#include "buffer/simple_buffer.h"
#include "operation/fill.h"

#include <catch.hpp>

TEMPLATE_TEST_CASE("gd::fill() is correct on SimpleBuffer<float,*>",
                   "[buffer]",
                   gd::buffer::SimpleBuffer<float>,
                   gd::buffer::m128::SimpleBuffer<float>)
{
    TestType buffer(256, 256, 8);
    gd::fill(buffer, 3.5f);

    for (size_t z = 0; z < 8; ++z)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            for (size_t x = 0; x < 256; ++x)
            {
                REQUIRE(buffer(z, y, x) == 3.5f);
            }
        }
    }
}

TEMPLATE_TEST_CASE("gd::m128::fill() is correct on SimpleBuffer<float,*>",
                   "[buffer]",
                   gd::buffer::SimpleBuffer<float>,
                   gd::buffer::m128::SimpleBuffer<float>)
{
    TestType buffer(256, 256, 8);
    gd::m128::fill(buffer, 3.5f);

    for (size_t z = 0; z < 8; ++z)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            for (size_t x = 0; x < 256; ++x)
            {
                REQUIRE(buffer(z, y, x) == 3.5f);
            }
        }
    }
}