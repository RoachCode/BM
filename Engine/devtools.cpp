#pragma once
#include "devtools.h"

DevTools::DevTools()
{
    counter = 0;
    fps = 60;
}

void DevTools::calculateFPS()
{
    time = clock.getElapsedTime();
    if (time.asMilliseconds() < 1000)
    {
        counter++;
    }
    else
    {
        clock.restart();
        fps = counter;
        counter = 0;
    }
}

std::string DevTools::getFPS()
{
    calculateFPS();
    std::string th{ std::to_string(fps) };
    return th;//_fps;
}

void DevTools::log(std::string in)
{
    std::cout << in << '\n';
}