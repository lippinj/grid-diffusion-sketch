#include "buffer/simple_buffer.h"
#include "operation.h"
#include "traversal.h"

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

TEMPLATE_TEST_CASE("SimpleBuffer increment() produces correct results",
                   "[buffer]",
                   gd::buffer::SimpleBuffer<float>,
                   gd::buffer::SimpleBuffer<int>,
                   gd::buffer::m128::SimpleBuffer<float>,
                   gd::buffer::m128::SimpleBuffer<int>)
{
    TestType A(64, 64, 8);
    TestType B(64, 64, 8);
    gd::fill<typename TestType::DataType>(A, 0);
    gd::fill<typename TestType::DataType>(B, 0);

    SECTION("After running increment() on A -> B")
    {
        gd::traversal::linearPairwise(B, A, gd::increment<typename TestType::DataType>());

        SECTION("Each cell in B has been incremented once per neighbor")
        {
            for (size_t x : {0, 1, 5, 14, 15, 62, 63})
            {
                for (size_t y : {0, 1, 5, 14, 15, 62, 63})
                {
                    for (size_t z : {0, 1, 2, 3, 4, 5, 6, 7})
                    {
                        const bool x_internal = (x > 0) && (x < 63);
                        const bool y_internal = (y > 0) && (y < 63);
                        const bool z_internal = (z > 0) && (z < 7);

                        const int num_axes_internal =
                            int(x_internal) + int(y_internal) + int(z_internal);
                        const bool is_internal = num_axes_internal == 3;
                        const bool is_face = num_axes_internal == 2;
                        const bool is_edge = num_axes_internal == 1;
                        const bool is_corner = num_axes_internal == 0;

                        if (is_internal)
                        {
                            REQUIRE(B(z, y, x) == 6);
                        }
                        if (is_face)
                        {
                            REQUIRE(B(z, y, x) == 5);
                        }
                        if (is_edge)
                        {
                            REQUIRE(B(z, y, x) == 4);
                        }
                        if (is_corner)
                        {
                            REQUIRE(B(z, y, x) == 3);
                        }
                    }
                }
            }
        }
        SECTION("The values in A remain at zero")
        {
            for (size_t x : {0, 1, 5, 14, 15})
            {
                for (size_t y : {0, 1, 5, 14, 15})
                {
                    for (size_t z : {0, 1, 2, 3, 4, 5, 6, 7})
                    {
                        REQUIRE(A(z, y, x) == 0);
                    }
                }
            }
        }
    }
}