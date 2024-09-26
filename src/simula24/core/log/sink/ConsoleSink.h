#ifndef CORE_LOG_SINK_CONSOLE_SINK_H_
#define CORE_LOG_SINK_CONSOLE_SINK_H_

#include <simula24/core/log/sink/BaseSink.h>

namespace simula24
{

///
/// @brief 
///     Sink that prints logs to stderr
/// 
class ConsoleSink : public BaseSink
{
public:
    ConsoleSink() {};
    
    bool supportsColor() override { return true; }

    void log(const simula24::string& msg) override;

    void flush() override;
};

} // radium

#endif // CORE_LOG_SINK_CONSOLE_SINK_H_