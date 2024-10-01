# Logging

Simula24's loggers are composed of two components: a base logger, and a sink. Using this model,
the logger constructs the output and the sink does *something* with the output (e.g. writing to a file)

## Construction

All logges must have a name and can optionally be created with a sink in place.
```C++
#include <core/log/log.h>

// no sink
simula24::Logger lawger1("lawg");

// with sink, these MUST derive from simula24::BaseSink

// no sink constructor arguments
simula24::Logger lawger2 = simula24::Logger::createLogger<ConsoleSink>("lawg");

// with sink constructor arguments

simula24::Logger flawger2 = simula24::Logger::createLogger<FileSink>("filelawg", "lawg.txt");

```

## Sinks

A sink simply operates on output. You could technically have a sink independent of the logger.

To log with a sink, you can call the `log` function and pass it a `stl::string`.

## Using the loggers

There are 5 log levels:
1. Info
2. Debug
3. Warning
4. Error
5. Critical

These are stored in the `simula24::LogLevel` enum class.

To create a log, you can call the log function for any given `Logger`. You must pass
a log level, a string, and optional format arguments.

```C++

using simula24::Logger;

Logger myLoggger = Logger::createLogger<ConsoleSink>("logg");

myLoggger.log(LogLevel::INFO, "My message with no format");

myLoggger.log(LogLevel::INFO, "My message with %d format argument", 1);

```

Note that the `Logger` will automatically append a newline to logs.

### Log Level functions

Writing `myLogger.log(LogLevel::INFO,....)` will get tedious *fast*.

Instead you an use functions like `Logger::info`, `Logger::critical`, etc.

These are templated wrappers around `Logger::log` that pass ``LogLevel``s for you.

```
Logger loggMan = Logger::createLogger<ConsoleSink>("Logg");

loggMan.warning("I am a warning");

loggMan.critical("haha I'm going to crash your app").
```

### Log Filters

You can also set the lowest `LogLevel` you want to receive logs for:

```C++

Logger logan = Logger::createLogger<ConsoleSink>("logan");

logan.setLogFilter(LogLevel::WARNING);

logan.info("I will be ignored");
logan.debug("As will I");
logan.warning("I will not be");

```

The default is `LogLevel::INFO`.

### Engine/Client Loggers

Simula24 has two built in loggers, one meant for the engine, one for the game/client.
These are found in the `DebugLoggers` class.

To make logging easier, 10 macros have been defined, 1 for each logger/log level.

```C++
#include <core/log/log.h>

ENGINE_CRITICAL("THE DEVS HAVE DONE SOMETHING STUPID");

CLIENT_ERROR("THE PLAYER HAS DONE SOMETHING STUPID");

```
