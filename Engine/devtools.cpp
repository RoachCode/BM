#pragma once
#include "devtools.h"

DevTools::DevTools()
{
    counter = 0;
}

int DevTools::calculateFPS()
{
    time = clock.getElapsedTime();
    if (time.asMilliseconds() < 1000)
    {
        counter++;
        return 0;
    }
    else
    {
        clock.restart();
        int result { counter };
        counter = 0;
        return result;
    }
}

int DevTools::getFPS()
{
    int fps{ this->calculateFPS() };
    if (fps > 0)
    {
        return fps;
    }
}

void DevTools::log(auto in)
{
    std::cout << in << '\n';
}