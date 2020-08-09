#include "bench.h"
#include "buffer.h"
#include "operation.h"
#include "traversal.h"

#include <iostream>

int main()
{
    const size_t N = 1024;
    const size_t M = 64;
    gd::buffer::SimpleBuffer<float> A(N, N, M);
    gd::buffer::SimpleBuffer<float> B(N, N, M);

    bench::measure("Zero fill A", 10, [&] { gd::fill(A, 0.0f); });
    bench::measure("Zero fill B", 10, [&] { gd::fill(B, 0.0f); });
    A(10, 10, 10) = 1.0f;

    bench::measure("Copy A to B", 10, [&] { gd::copy(B, A); });

    bench::measure("Apply heat exchange", 10, [&] {
        gd::traversal::linearPairwise(B, A, gd::exchangeHeat(0.01f));
    });

    return 0;
}