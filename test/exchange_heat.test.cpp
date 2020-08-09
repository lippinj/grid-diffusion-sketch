#include "buffer/simple_buffer.h"
#include "operation/copy.h"
#include "operation/exchange_heat.h"
#include "operation/fill.h"
#include "traversal/linear_pairwise.h"

#include <catch.hpp>

TEMPLATE_TEST_CASE("gd::exchangeHeat() is correct on SimpleBuffer<float,*>",
                   "[buffer]",
                   gd::buffer::SimpleBuffer<float>,
                   gd::buffer::m128::SimpleBuffer<float>)
{
    size_t x = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 31, 32, 61, 62);
    size_t y = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 31, 32, 61, 62);
    size_t z = GENERATE(1, 2, 3, 4, 5, 6);

    TestType src(64, 64, 8);
    TestType dst(64, 64, 8);

    gd::fill(src, 0.0f);
    src(z, y, x) = 1.0f;
    gd::copy(dst, src);

    gd::traversal::linearPairwise(dst, src, gd::exchangeHeat(0.01f));

    for (int dz : {-1, 0, 1})
    {
        for (int dy : {-1, 0, 1})
        {
            for (int dx : {-1, 0, 1})
            {
                const int steps = std::abs(dz) + std::abs(dy) + std::abs(dx);
                {
                    const float value = dst(z + dz, y + dy, x + dx);
                    if (steps == 0)
                    {
                        REQUIRE(value == Approx(0.94f));
                    }
                    else if (steps == 1)
                    {
                        REQUIRE(value == Approx(0.01f));
                    }
                    else
                    {
                        REQUIRE(value == Approx(0.00f));
                    }
                }
            }
        }
    }
}

TEMPLATE_TEST_CASE(
    "gd::m128::exchangeHeat() is correct on SimpleBuffer<float,*>",
    "[buffer]",
    gd::buffer::m128::SimpleBuffer<float>)
{
    size_t x = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 31, 32, 61, 62);
    size_t y = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 31, 32, 61, 62);
    size_t z = GENERATE(1, 2, 3, 4, 5, 6);

    TestType src(64, 64, 8);
    TestType dst(64, 64, 8);

    gd::m128::fill(src, 0.0f);
    src(z, y, x) = 1.0f;
    gd::m128::copy(dst, src);

    gd::traversal::m128::linearPairwise(
        dst, src, gd::exchangeHeat(0.01f), gd::m128::exchangeHeat(0.01f));

    for (int dz : {-1, 0, 1})
    {
        for (int dy : {-1, 0, 1})
        {
            for (int dx : {-1, 0, 1})
            {
                const int steps = std::abs(dz) + std::abs(dy) + std::abs(dx);
                {
                    const float value = dst(z + dz, y + dy, x + dx);
                    if (steps == 0)
                    {
                        REQUIRE(value == Approx(0.94f));
                    }
                    else if (steps == 1)
                    {
                        REQUIRE(value == Approx(0.01f));
                    }
                    else
                    {
                        REQUIRE(value == Approx(0.00f));
                    }
                }
            }
        }
    }
}