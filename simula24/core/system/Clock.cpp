#include <core/system/Clock.h>
#include <SDL_Timer.h>
#include <core/types.h>

using simula24::Clock;
using simula24::U64;

Clock::Clock()
    : m_delta(0.0f), m_pausedTime(0), m_baseTime(0),
    m_prevTime(0), m_curTime(0), 
    m_secPerCount(0.0f),
    paused(false), m_endTime(0)
{
    m_secPerCount = 1000.0f / (double)SDL_GetPerformanceFrequency();
}

float Clock::getTotal() const
{
    if (paused)
        return (float)(((m_endTime - m_pausedTime) - m_baseTime) * m_secPerCount);
    else
        return (float)(((m_curTime - m_pausedTime) - m_baseTime) * m_secPerCount);
}

void Clock::reset()
{
    U64 now = SDL_GetPerformanceCounter();
    paused = false;
    m_baseTime = now;
    m_prevTime = now;
    m_endTime = 0;
}

void Clock::start()
{
    U64 startTime = SDL_GetPerformanceCounter();
    if (paused)
    {
        m_pausedTime += (startTime - m_endTime);
        m_prevTime = startTime;
        m_endTime = 0;
        paused = false;
    }
}

void Clock::stop()
{
    if (!paused)
    {
        U64 curTime = SDL_GetPerformanceCounter();
        m_endTime = curTime;
        paused = true;
    }
}

void Clock::tick()
{
    if (paused)
    {
        m_delta = 0.0;
        return;
    }

    U64 curTime = SDL_GetPerformanceCounter();
    m_curTime = curTime;
    m_delta = (curTime - m_prevTime) * m_secPerCount;
    m_prevTime = m_curTime;
    if (m_delta < 0.0f)
        m_delta = 0.0f;

}