#ifndef BENCH_MEASURE_H
#define BENCH_MEASURE_H

#include "timer.h"

#include <cstdio>
#include <functional>
#include <string>
#include <vector>

namespace bench
{
void measure(const std::string& name,
             unsigned int repetitions,
             std::function<void()> target)
{
    Timer timer;

    if (repetitions > 1)
    {
        std::printf("%-24s %3dx", name.c_str(), repetitions);

        std::vector<double> times;
        for (unsigned int i = 0; i < repetitions; ++i)
        {
            timer.start();
            target();
            timer.stop();
            times.push_back(timer.elapsedTime());
        }

        double total = 0.0;
        double smallest = times[0];
        double greatest = times[0];
        for (const auto time : times)
        {
            total += time;
            smallest = std::min(time, smallest);
            greatest = std::max(time, greatest);
        }
        double mean = total / repetitions;

        std::printf("  in %5.1f ms (%.1f .. %.1f)\n",
                    (1000.0 * mean),
                    (1000.0 * smallest),
                    (1000.0 * greatest));
    }
    else
    {
        std::printf("%-29s", name.c_str());
        timer.start();
        target();
        timer.stop();
        std::printf("  in %5.1f ms\n", (1000.0 * timer.elapsedTime()));
    }
}

} // namespace bench

#endif