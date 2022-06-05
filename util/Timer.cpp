#include "Timer.h"

void Timer::Start()
{
    start = chrono::steady_clock::now();
}

double Timer::GetDuration()
{
    end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}