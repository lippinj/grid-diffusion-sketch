#include "grid.h"
#include "operation.h"
#include "pairwise.h"
#include "timer.h"

#include <iostream>

int main()
{
    Timer timer;

    const size_t N = 1024;
    const size_t M = 64;
    Grid<float> temps_a(N, N, M);
    Grid<float> temps_b(N, N, M);

    temps_a.fill(0.0);
    temps_b.fill(0.0);
    temps_a.cell(10, 10, 10) = 1.0f;

    {
        std::cout << "Default" << std::endl;

        timer.start();
        for (size_t z = 0; z < M; ++z)
        {
            std::copy(temps_a.levelBegin(z),
                      temps_a.levelEnd(z),
                      temps_b.levelBegin(z));
        }
        timer.stop();
        std::cout << "  Copy time:  " << timer.elapsedTime() << std::endl;

        timer.start();
        pairwise(temps_b, temps_a, heatTransfer(0.01f));
        timer.stop();

        std::cout << "  Op time:    " << timer.elapsedTime() << std::endl;
        std::cout << "  Per slice:  " << (timer.elapsedTime() / M) << std::endl;
    }

    {
        std::cout << "With OpenMP" << std::endl;

        timer.start();
#pragma omp parallel for
        for (size_t z = 0; z < M; ++z)
        {
            std::copy(temps_a.levelBegin(z),
                      temps_a.levelEnd(z),
                      temps_b.levelBegin(z));
        }
        timer.stop();
        std::cout << "  Copy time:  " << timer.elapsedTime() << std::endl;

        timer.start();
        pairwiseParallel(temps_b, temps_a, heatTransfer(0.01f));
        timer.stop();

        std::cout << "  Op time:    " << timer.elapsedTime() << std::endl;
        std::cout << "  Per slice:  " << (timer.elapsedTime() / M) << std::endl;
    }

    return 0;
}