#ifndef SIMULA24_CORE_LOG_SINK_FILE_SINK_H_
#define SIMULA24_CORE_LOG_SINK_FILE_SINK_H_

#include <simula24/core/stl/string.h>
#include <simula24/core/stl/array.h>
#include <simula24/core/log/sink/BaseSink.h>

#include <stdio.h>
//#define DEFAULT_FLUSH_RATE 10
namespace simula24
{

///
/// @brief
///     Write logs to a file
/// 
///     This will write logs to a file every <i>n</i> logs sent to it
///     This works by using an internal cache of recent logs (@ref m_logCache)
/// 
///     You can configure this in the constructor by setting the `flushRate` parameter
/// 
///     Any remaining logs will automatically be flushed during destruction
/// 
class FileSink : public BaseSink
{
public:
    static constexpr int DEFAULT_FLUSH_RATE = 10;
    FileSink(const stl::string& filename, int flushRate = DEFAULT_FLUSH_RATE);
    FileSink(const char* filename, int flushRate = DEFAULT_FLUSH_RATE);

    ~FileSink();

    bool supportsColor() override { return false; }

    void log(const stl::string& msg) override;

    void flush() override;

private:
    int m_flushRate;
    int m_curFlushInterval;

    FILE* m_out;

    stl::array<stl::string> m_logCache;

    bool openFile(const char* name);
};

} // radium


#endif // SIMULA24_CORE_LOG_SINK_FILE_SINK_H_