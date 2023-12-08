#pragma once
#include "devtools.h"

// Public
DevTools::DevTools()
{
    m_freeMovementAllowed = false;
    m_counter = 0;
    m_fps = 0;
    wallToggleBool = false;
}

const bool DevTools::queryFreeMovement()
{
    return m_freeMovementAllowed;
}

void DevTools::toggleFreeMovement()
{
    m_freeMovementAllowed = !m_freeMovementAllowed;
}

const std::string DevTools::getFPS()
{
    m_calculateFPS();
    return std::to_string(m_fps);
}

const void DevTools::log(std::string in)
{
    std::cout << in << '\n';
}

void DevTools::wallToggle()
{
    wallToggleBool = !wallToggleBool;
}
// Private
void DevTools::m_calculateFPS()
{
    sf::Time time = m_clock.getElapsedTime();
    if (time.asMilliseconds() < 1000)
    {
        m_counter++;
    }
    else
    {
        m_clock.restart();
        m_fps = m_counter;
        m_counter = 0;
    }
}