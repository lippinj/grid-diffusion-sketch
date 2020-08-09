#include "bench.h"
#include "buffer.h"
#include "operation.h"
#include "traversal.h"

#include <iostream>

template<unsigned int Alignment = 1>
void benchmarkSimple(const size_t N, const size_t M)
{
    gd::buffer::SimpleBuffer<float, Alignment> A(N, N, M);
    gd::buffer::SimpleBuffer<float, Alignment> B(N, N, M);

    bench::measure("Zero fill A", 10, [&] { gd::fill(A, 0.0f); });
    bench::measure("Zero fill B", 10, [&] { gd::fill(B, 0.0f); });
    A(10, 10, 10) = 1.0f;

    bench::measure("Copy A to B", 10, [&] { gd::copy(B, A); });

    bench::measure("Apply heat exchange", 10, [&] {
        gd::traversal::linearPairwise(B, A, gd::exchangeHeat(0.01f));
    });
}

void benchmarkSimpleM128(const size_t N, const size_t M)
{
    gd::buffer::m128::SimpleBuffer<float> A(N, N, M);
    gd::buffer::m128::SimpleBuffer<float> B(N, N, M);

    bench::measure("Zero fill A", 10, [&] { gd::m128::fill(A, 0.0f); });
    bench::measure("Zero fill B", 10, [&] { gd::m128::fill(B, 0.0f); });
    A(10, 10, 10) = 1.0f;

    bench::measure("Copy A to B", 10, [&] { gd::m128::copy(B, A); });

    bench::measure("Apply heat exchange", 10, [&] {
        gd::traversal::linearPairwise(B, A, gd::exchangeHeat(0.01f));
    });
}

int main()
{
    std::cout << "SIMPLE M128" << std::endl;
    benchmarkSimpleM128(1024, 64);

    std::cout << std::endl;
    std::cout << "SIMPLE<16>" << std::endl;
    benchmarkSimple<16>(1024, 64);

    std::cout << std::endl;
    std::cout << "SIMPLE" << std::endl;
    benchmarkSimple(1024, 64);

    return 0;
}