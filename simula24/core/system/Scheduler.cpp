#include "Scheduler.h"
#include <cstdio>
using simula24::Scheduler;
using simula24::Clock;
using simula24::U32;

void Scheduler::start()
{
    m_clock.start();
    m_clock.tick();

    m_last = m_clock.getTotal();
}


void Scheduler::update()
{
    m_clock.tick();
    float now = m_clock.getTotal();
    if ((now - m_last) >= m_period)
    {
        m_fn();
        m_last = now;
    }
}
