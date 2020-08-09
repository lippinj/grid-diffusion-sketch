#include "grid.h"
#include "operation.h"
#include "pairwise.h"

#include <catch.hpp>

TEMPLATE_TEST_CASE("Given some read-only grid",
                   "[grid]",
                   Grid<float>,
                   Grid<int>,
                   const Grid<float>,
                   const Grid<int>)
{
    TestType grid(16, 16, 8);

    SECTION("The buffer locations for different levels are distinct")
    {
        const size_t zi = GENERATE(range(0, 8));
        const size_t zj = GENERATE(range(0, 8));

        if (zi != zj)
        {
            REQUIRE(grid.levelBegin(zi) != grid.levelBegin(zj));
        }
    }

    SECTION("The buffer locations for different lines are distinct")
    {
        const size_t z = GENERATE(range(0, 8));
        const size_t yi = GENERATE(range(0, 16));
        const size_t yj = GENERATE(range(0, 16));

        if (yi != yj)
        {
            REQUIRE(grid.lineBegin(z, yi) != grid.lineBegin(z, yj));
        }
    }

    SECTION("The level and first-line pointers agree")
    {
        const size_t z = GENERATE(range(0, 8));
        REQUIRE(grid.lineBegin(z, 0) == grid.levelBegin(z));
    }

    SECTION("The cell and line pointers agree")
    {
        const size_t x = GENERATE(range(0, 16));
        const size_t y = GENERATE(range(0, 16));
        const size_t z = GENERATE(range(0, 8));
        REQUIRE(&grid.cell(x, y, z) == grid.lineBegin(z, y) + x);
    }
}

TEST_CASE("Given some grid which we fill", "[grid]")
{
    Grid<float> grid(64, 64, 8);
    grid.fill(2.5);

    SECTION("The values show up as the value we chose")
    {
        const size_t x = GENERATE(0, 1, 5, 14, 15);
        const size_t y = GENERATE(0, 1, 5, 14, 15);
        const size_t z = GENERATE(range(0, 8));
        REQUIRE(grid.cell(x, y, z) == 2.5);
    }
}

TEST_CASE("Given some two grids, initialized to zero", "[grid]")
{
    Grid<float> A(64, 64, 8);
    Grid<float> B(64, 64, 8);
    A.fill(0);
    B.fill(0);

    SECTION("After running increment() on A -> B")
    {
        pairwise(B, A, increment<float>());

        SECTION("Each cell in B has been incremented once per neighbor")
        {
            const size_t x = GENERATE(0, 1, 5, 14, 15, 62, 63);
            const size_t y = GENERATE(0, 1, 5, 14, 15, 62, 63);
            const size_t z = GENERATE(range(0, 8));

            const bool x_internal = (x > 0) && (x < 63);
            const bool y_internal = (y > 0) && (y < 63);
            const bool z_internal = (z > 0) && (z < 7);

            const int num_axes_internal = int(x_internal) + int(y_internal) + int(z_internal);
            const bool is_internal = num_axes_internal == 3;
            const bool is_face = num_axes_internal == 2;
            const bool is_edge = num_axes_internal == 1;
            const bool is_corner = num_axes_internal == 0;

            REQUIRE((is_internal || is_face || is_edge || is_corner));

            SECTION("Internal cells have 6 neighbors")
            {
                if (is_internal)
                {
                    REQUIRE(B.cell(x, y, z) == 6.0);
                }
            }
            SECTION("Cube face cells have 5 neighbors")
            {
                if (is_face)
                {
                    REQUIRE(B.cell(x, y, z) == 5.0);
                }
            }
            SECTION("Cube edge cells have 4 neighbors")
            {
                if (is_edge)
                {
                    REQUIRE(B.cell(x, y, z) == 4.0);
                }
            }
            SECTION("Cube corner cells have 3 neighbors")
            {
                if (is_corner)
                {
                    REQUIRE(B.cell(x, y, z) == 3.0);
                }
            }
        }
        SECTION("The values in A remain at zero")
        {
            const size_t x = GENERATE(0, 1, 5, 14, 15);
            const size_t y = GENERATE(0, 1, 5, 14, 15);
            const size_t z = GENERATE(range(0, 8));
            REQUIRE(A.cell(x, y, z) == 0.0);
        }
    }
}