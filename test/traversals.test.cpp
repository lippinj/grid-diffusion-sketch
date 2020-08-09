#include "grid.h"
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

TEST_CASE("Given some two grids, initialized to zero", "[grid]")
{
    Grid<float> A(64, 64, 8);
    Grid<float> B(64, 64, 8);
    A.fill(0);
    B.fill(0);

    SECTION("The values show up as zero")
    {
        const size_t x = GENERATE(0, 1, 5, 14, 15);
        const size_t y = GENERATE(0, 1, 5, 14, 15);
        const size_t z = GENERATE(range(0, 8));
        REQUIRE(A.cell(x, y, z) == 0);
        REQUIRE(B.cell(x, y, z) == 0);
    }
}