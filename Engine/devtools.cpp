#pragma once
#include "devtools.h"
#include <iostream>

DevTools::DevTools()
{
    counter = 0;
}

int DevTools::getFPS()
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

void DevTools::showFPS()
{
    int fps{ this->getFPS() };
    if (fps > 0)
    {
        std::cout << fps << '\n';
    }
}