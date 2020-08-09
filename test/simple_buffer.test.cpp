#include "buffer/simple_buffer.h"

#include <catch.hpp>

TEMPLATE_TEST_CASE(
    "SimpleBuffer buffer locations returned by operator() are sane",
    "[buffer]",
    gd::buffer::SimpleBuffer<float>,
    gd::buffer::SimpleBuffer<int>,
    gd::buffer::m128::SimpleBuffer<float>,
    gd::buffer::m128::SimpleBuffer<int>,
    const gd::buffer::SimpleBuffer<float>,
    const gd::buffer::SimpleBuffer<int>,
    const gd::buffer::m128::SimpleBuffer<float>,
    const gd::buffer::m128::SimpleBuffer<int>)
{
    TestType buffer(16, 16, 8);

    SECTION("The buffer locations for different levels are distinct")
    {
        for (size_t zi = 0; zi < 8; ++zi)
        {
            for (size_t zj = 0; zj < 8; ++zj)
            {
                if (zi != zj)
                {
                    REQUIRE(buffer(zi) != buffer(zj));
                }
            }
        }
    }

    SECTION("The buffer locations for different lines are distinct")
    {
        for (size_t z = 0; z < 8; ++z)
        {
            for (size_t yi = 0; yi < 16; ++yi)
            {
                for (size_t yj = 0; yj < 8; ++yj)
                {
                    if (yi != yj)
                    {
                        REQUIRE(buffer(z, yi) != buffer(z, yj));
                    }
                }
            }
        }
    }

    SECTION("The level and first-line pointers agree")
    {
        for (size_t z = 0; z < 8; ++z)
        {
            REQUIRE(buffer(z, 0) == buffer(z));
        }
    }

    SECTION("The cell and line pointers agree")
    {
        for (size_t z = 0; z < 8; ++z)
        {
            for (size_t y = 0; y < 16; ++y)
            {
                for (size_t x = 0; x < 16; ++x)
                {
                    REQUIRE(&buffer(z, y, x) == buffer(z, y) + x);
                }
            }
        }
    }
}