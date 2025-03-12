#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <conio.h>  // For _kbhit() and _getch()
#include <thread>
// 스탑워치 구현
class Stopwatch 
{
public:
    Stopwatch() : running(false), start_time(), end_time() {}

    void start() 
    {
        if (!running) 
        {
            running = true;
            start_time = std::chrono::high_resolution_clock::now();
        }
    }

    void stop() 
    {
        if (running) 
        {
            end_time = std::chrono::high_resolution_clock::now();
            running = false;
        }
    }

    void reset() 
    {
        running = false;
    }

    double elapsed_seconds() const 
    {
        if (running) 
        {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - start_time;
            return elapsed.count();
        }
        else 
        {
            std::chrono::duration<double> elapsed = end_time - start_time;
            return elapsed.count();
        }
    }

    void print_elapsed() const 
    {
        double seconds = elapsed_seconds();
        int minutes = static_cast<int>(seconds) / 60;
        int seconds_remaining = static_cast<int>(seconds) % 60;
        int milliseconds = static_cast<int>((seconds - static_cast<int>(seconds)) * 100);

        std::cout << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds_remaining << "."
            << std::setw(2) << std::setfill('0') << milliseconds << std::flush;
    }

private:
    bool running;
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};

Stopwatch sw;