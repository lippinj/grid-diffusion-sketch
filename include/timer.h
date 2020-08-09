#ifndef GD_TIMER_H
#define GD_TIMER_H

#include <chrono>

class Timer
{
public:
    void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop()
    {
        stop_time = std::chrono::high_resolution_clock::now();
    }

    double elapsedTime() const
    {
        return std::chrono::duration<double>(stop_time - start_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point stop_time;
};

#endif