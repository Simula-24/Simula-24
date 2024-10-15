#ifndef CORE_SYSTEM_CLOCK_H_
#define CORE_SYSTEM_CLOCK_H_

#include <core/types.h>

namespace simula24
{

///
/// @brief
///     Time keeper
///
class Clock
{
public:
    Clock();

    FORCEINLINE float getDelta() const { return static_cast<float>(m_delta); }
    float getTotal() const;


    void reset();

    ///
    /// @brief
    ///     Starts the clock if it was paused
    ///     This will add the ammount of time paused
    ///     to the paused-time-counter
    /// 
    /// 
    ///                  |<--------pt------->|
    /// ----*------------*-------------------*------------->
    ///  m_baseTime  m_endTime           m_startTime           
    /// 
    /// pt is added to pause time
    /// 
    void start();

    /// Pause the clock
    /// Subsequent calls to tick will return 0
    void stop();

    /// increment the clock
    void tick();

private:
    double m_delta;

    U64 m_pausedTime;
    U64 m_baseTime;
    U64 m_prevTime;
    U64 m_curTime;
    U64 m_endTime;
    double m_secPerCount;

    bool paused;
};

} // simula24


#endif // CORE_SYSTEM_CLOCK_H_