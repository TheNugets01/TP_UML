#pragma once
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <algorithm>
#include<vector>

using namespace std;

class Timer
{
public:
    void Start();
    double GetDuration();
private:
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;
};