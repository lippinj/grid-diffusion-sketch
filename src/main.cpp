#include "grid.h"
#include "heat.h"
#include "timer.h"

#include <iostream>

int main()
{
    Timer timer;

    Grid<float> temps_a(1024, 1024, 64);
    Grid<float> temps_b(1024, 1024, 64);

    temps_a.fill(0.0);
    temps_b.fill(0.0);
    temps_a.cell(10, 10, 10) = 1.0f;

    {
        std::cout << "Default" << std::endl;

        timer.start();
        heatApply(temps_b, temps_a);
        timer.stop();

        std::cout << "  Total time: " << timer.elapsedTime() << std::endl;
        std::cout << "  Per slice: " << (timer.elapsedTime() / 64) << std::endl;
    }

    {
        std::cout << "With OpenMP" << std::endl;

        timer.start();
        heatApplyParallel(temps_b, temps_a);
        timer.stop();

        std::cout << "  Total time: " << timer.elapsedTime() << std::endl;
        std::cout << "  Per slice: " << (timer.elapsedTime() / 64) << std::endl;
    }

    return 0;
}