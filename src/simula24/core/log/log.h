#ifndef SIMULA24_CORE_LOG_LOG_H_
#define SIMULA24_CORE_LOG_LOG_H_

#include <simula24/core/stl/string.h>
#include <simula24/core/stl/utility.h>
#include <simula24/core/log/colors.h>
#include <simula24/core/log/sink/BaseSink.h>
#include <stdarg.h>
#include <type_traits>


namespace simula24
{

enum class LogLevel : int
{
    DEBUG,
    INFO,
    WARNING,
    ERROR_,
    CRITICAL
};


///
/// @brief 
///     Logging Class
/// 
///     The Logger class is responsible for constructing output
///     
///     Output of the logs is delegated to an @ref BaseS
///     
///     Logger::setSink<Type>() creates a new output system
///     
///     Logger::setSink<Type>(ConstructionArgs&&...) creates a new output system
///                                            and passes args... to its constructor
/// 
///     Logger::info, Logger::debug, etc. are wrappers around Logger::log
///     
/// 
class Logger
{
public:

    Logger(const simula24::string& name)
        : m_name(simula24::move(name)), m_sink{ nullptr }, m_lowestLevel(LogLevel::INFO)
    {}
    Logger(const char* name) : m_name(name), m_sink{ nullptr } {}
    ~Logger();

    ///
    /// @brief
    ///     Log to the @ref BaseSink
    /// 
    ///     1. Log with LogLevel ll
    ///     2. Construct a log based on msg and args
    ///     3. Forward constructed log to the output system
    ///     
    void log(LogLevel ll, const char* msg, ...);

    ///
    /// @brief
    ///     Log a section of memory from start to start + length
    ///     This does NOT detect if you are reading from an area of memory 
    ///     that has been freed or does not belong to you
    /// 
    void logMemorySection(const void* start, int length, const char* msg, ...);

    void setLogFilter(LogLevel ll) { m_lowestLevel = ll; }


    /// Set the output system
    template <class SinkType>
    void setSink()
    {
        static_assert(std::is_base_of_v<simula24::BaseSink, SinkType> && "SinkType must derive from simula24::BaseSink");

        if (m_sink)
            delete m_sink;
        m_sink = new SinkType();
    }

    /// Set the output system and pass @ref ConstructionArgs to its constructor
    template <class SinkType, class...ConstructionArgs>
    void setSink(ConstructionArgs&&... args)
    {
        static_assert(std::is_base_of_v<simula24::BaseSink, SinkType> && "SinkType must derive from simula24::BaseSink");

        if (m_sink)
            delete m_sink;
        m_sink = new SinkType(simula24::forward<ConstructionArgs>(args)...);
    }

    /// fwds to Log with LogLevel::DEBUG
    template<class... Args>
    constexpr void debug(const char* message, Args&&... args)
    {
        log(LogLevel::DEBUG, message, simula24::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::INFO
    template <class... Args>
    constexpr void info(const char* message, Args&&... args)
    {
        log(LogLevel::INFO, message, simula24::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::WARNING
    template <class... Args>
    constexpr void warning(const char* message, Args&&... args)
    {
        log(LogLevel::WARNING, message, simula24::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::ERROR
    template <class... Args>
    constexpr void error(const char* message, Args&&... args)
    {
        log(LogLevel::ERROR_, message, simula24::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::CRITICAL
    template <class... Args>
    constexpr void critical(const char* message, Args&&... args)
    {
        log(LogLevel::CRITICAL, message, simula24::forward<Args>(args)...);
    }

private:

    BaseSink* m_sink;

    string m_name;
    
    LogLevel m_lowestLevel;

    const char* m_colorMap[5] =
    {
        {Colors::GREEN}, /// DEBUG
        {Colors::GREEN}, /// INFO
        {Colors::YELLOW},/// WARNING
        {Colors::RED},   /// ERROR
        {Colors::RED}    /// CRITICAL
    };

    /// Add current time + logger name
    void writeMetaData(string& output);

    /// write the log level (in color if supported, see @ref BaseSink::supportsColor())
    void writeLogLevel(LogLevel ll, string& output);

    /// Add the users formatted arguments to the output, uses vsnprintf
    void writeUserMessage(string& output, const char* message, va_list args);

};


} // simula24


#endif //SIMULA24_CORE_LOG_LOG_H_