#ifndef SIMULA24_CORE_LOG_SINK_BASE_SINK_H_
#define SIMULA24_CORE_LOG_SINK_BASE_SINK_H_

#include <simula24/core/stl/string.h>

namespace simula24
{

///
/// @brief 
///     Base class for logging strategies
/// 
class BaseSink
{
public:
    virtual bool supportsColor() = 0;
    virtual void log(const simula24::string& msg) = 0;
    virtual void flush() = 0;
    virtual ~BaseSink() {}
};

} // radium

#endif // SIMULA24_CORE_LOG_SINK_BASE_SINK_H_