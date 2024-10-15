#ifndef CORE_SYSTEM_SCHEDULER_H_
#define CORE_SYSTEM_SCHEDULER_H_

#include <core/types.h>
#include <core/stl/function.h>
//#include <core/stl/array.h>

#include <core/system/Clock.h>

namespace simula24
{

using ScheduledFunction = stl::function<void(void)>;


///
/// @brief
///     Scheduler: will call a void(void) function of your choice every
///     <period> seconds (this can be a decimal for milliseconds).
/// 
class Scheduler
{
public:
    
    template<class Function>
    Scheduler(float period, Function fn)
        : m_period(period), m_fn{ fn }, m_last(0), m_clock{}
    {}

    ///
    /// @brief
    ///     Update the timer, this will call the function
    ///     if the time period has elapsed
    /// 
    void update();

    ///
    /// @brief
    ///     Starts the timer
    /// 
    void start();
    
    void setPeriod(float period) { m_period = period; }
private:
    /// How many seconds to wait
    float m_period;
    
    /// Last time function was executed
    float m_last;
    
    Clock m_clock;
    
    ScheduledFunction m_fn;
};


}



#endif // CORE_SYSTEM_SCHEDULER_H_