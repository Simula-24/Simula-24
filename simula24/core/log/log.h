#ifndef SIMULA24_CORE_LOG_LOG_H_
#define SIMULA24_CORE_LOG_LOG_H_

#include <simula24/core/stl/string.h>
#include <simula24/core/stl/utility.h>
#include <simula24/core/log/colors.h>
#include <simula24/core/log/sink/BaseSink.h>
#include <core/stl/smart_ptr.h>
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

    /// the init-list code duplication IS necessary otherwise setSink will NOT work.
    explicit Logger(const stl::string& name)
        : m_sink{ nullptr }, m_name(name.c_str()), m_lowestLevel(LogLevel::DEBUG)
    {}
    explicit Logger(const char* name) : m_sink{ nullptr }, m_name(name), m_lowestLevel(LogLevel::DEBUG) {}
    ~Logger();

    ///
    /// @brief 
    ///     Construct a logger with a sink
    /// 
    template <class SinkType>
    static Logger createLogger(const stl::string& name)
        requires(std::is_base_of_v<simula24::BaseSink, SinkType>)
    {
        Logger newLogger(name);
        newLogger.setSink<SinkType>();
        return newLogger;
    }

    ///
    /// @brief 
    ///     Construct a logger with a sink and pass arguments to the sink's constructor
    /// 
    template <class SinkType, class... ConstructionArgs>
    static Logger createLogger(const stl::string& name, ConstructionArgs&&... args)
        requires(std::is_base_of_v<simula24::BaseSink, SinkType>)
    {
        Logger newLogger(name);
        newLogger.setSink<SinkType>(args...);
        return newLogger;
    }

    Logger(const Logger& ) = default;
    Logger& operator=(const Logger& ) = default;

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
        m_sink = new SinkType(stl::forward<ConstructionArgs>(args)...);
    }

    /// fwds to Log with LogLevel::DEBUG
    template<class... Args>
    constexpr void debug(const char* message, Args&&... args)
    {
        log(LogLevel::DEBUG, message, stl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::INFO
    template <class... Args>
    constexpr void info(const char* message, Args&&... args)
    {
        log(LogLevel::INFO, message, stl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::WARNING
    template <class... Args>
    constexpr void warning(const char* message, Args&&... args)
    {
        log(LogLevel::WARNING, message, stl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::ERROR
    template <class... Args>
    constexpr void error(const char* message, Args&&... args)
    {
        log(LogLevel::ERROR_, message, stl::forward<Args>(args)...);
    }

    /// fwds to Log with LogLevel::CRITICAL
    template <class... Args>
    constexpr void critical(const char* message, Args&&... args)
    {
        log(LogLevel::CRITICAL, message, stl::forward<Args>(args)...);
    }

private:

    BaseSink* m_sink;

    stl::string m_name;
    
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
    void writeMetaData(stl::string& output);

    /// write the log level (in color if supported, see @ref BaseSink::supportsColor())
    void writeLogLevel(LogLevel ll, stl::string& output);

    /// Add the users formatted arguments to the output, uses vsnprintf
    void writeUserMessage(stl::string& output, const char* message, va_list args);

};


class DebugLoggers
{
public:
    static void init();
    static stl::shared_ptr<Logger>& getEngineLogger() { return m_engineLogger; }
    static stl::shared_ptr<Logger>& getClientLogger() { return m_clientLogger; }
private:
    static stl::shared_ptr<Logger> m_engineLogger;
    static stl::shared_ptr<Logger> m_clientLogger;
};

} // simula24


#define ENGINE_INFO(...)       simula24::DebugLoggers::getEngineLogger()->info(__VA_ARGS__) 
#define ENGINE_DEBUG(...)      simula24::DebugLoggers::getEngineLogger()->debug(__VA_ARGS__) 
#define ENGINE_WARNING(...)    simula24::DebugLoggers::getEngineLogger()->warning(__VA_ARGS__)     
#define ENGINE_ERROR(...)      simula24::DebugLoggers::getEngineLogger()->error(__VA_ARGS__) 
#define ENGINE_CRITICAL(...)   simula24::DebugLoggers::getEngineLogger()->critical(__VA_ARGS__)

#define CLIENT_INFO(...)       simula24::DebugLoggers::getClientLogger()->info(__VA_ARGS__) 
#define CLIENT_DEBUG(...)      simula24::DebugLoggers::getClientLogger()->debug(__VA_ARGS__) 
#define CLIENT_WARNING(...)    simula24::DebugLoggers::getClientLogger()->warning(__VA_ARGS__)     
#define CLIENT_ERROR(...)      simula24::DebugLoggers::getClientLogger()->error(__VA_ARGS__) 
#define CLIENT_CRITICAL(...)   simula24::DebugLoggers::getClientLogger()->critical(__VA_ARGS__)

#endif //SIMULA24_CORE_LOG_LOG_H_