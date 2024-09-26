#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

#include <cassert>

using simula24::Logger;

static const char* LogNameMap[5] =
{
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

Logger::~Logger()
{
    if (m_sink)
        delete m_sink;
}

void Logger::log(LogLevel ll, const char* msg, ...)
{
    if (ll < m_lowestLevel)
        return;
    assert(m_sink);

    simula24::string output;

    output.resize(
        // 10 for max size of lognamemap var
        27 + m_name.length() + 25
    );

    writeMetaData(output);
    writeLogLevel(ll, output);

    va_list ap;
    va_start(ap, msg);

    writeUserMessage(output, msg, ap);

    va_end(ap);

    output += "\n";

    m_sink->log(output);
}

void Logger::logMemorySection(const void* start, int length, const char* msg, ...)
{
    assert(m_sink);

    simula24::string output;

    output.resize(
        // 10 for max size of lognamemap var
        27 + m_name.length() + 25 + 61
    );

    writeMetaData(output);

    va_list ap;
    va_start(ap, msg);
    writeUserMessage(output, msg, ap);
    va_end(ap);

    char memDumpMessage[20 + 2 + (16 * 2) + 7];

    int nullterm = snprintf(
        memDumpMessage,
        sizeof(memDumpMessage),
        "\nBEGIN MEMORY DUMP 0x%p - 0x%p\n",
        start, ((uint64_t*)start) + length
    );

    memDumpMessage[nullterm] = 0;

    output += memDumpMessage;
    char* buffer = new char[length * 6];

    int buflen = 0;

    for (int i = 0; i < length; i++)
    {
        int ri; // raw byte index
        for (ri = i; ri < i + 10; ri++)
        {
            if (ri >= length) break;
            buflen += sprintf(buffer + buflen, "%02x ", *((uint8_t*)start + ri));
        }

        // add spaces 
        for (int si = 0; si < (i - ri) + 11; si++)
        {
            buffer[buflen++] = ' ';
            buffer[buflen++] = ' ';
            buffer[buflen++] = ' ';
        }
        // print ascii representation 
        for (int bi = i; bi < ri; bi++)
        {
            uint8_t cur = *((uint8_t*)start + bi);

            if (cur >= 0x21 && cur <= 0x7e)
                buffer[buflen++] = cur;
            else
                buffer[buflen++] = '.';
        }

        i += (ri - i);

        buffer[buflen++] = '\n';

    }
    buffer[buflen++] = 0;

    output += buffer;
    output += "END MEMORY DUMP\n";

    m_sink->log(output);

    delete[] buffer;
}

void Logger::writeMetaData(simula24::string& output)
{
    char timeBuffer[25];

    time_t timeOfLog = time(NULL);
    struct tm* timeInfo = nullptr;
    timeInfo = localtime(&timeOfLog);

    strftime(timeBuffer, 24, "[%F %T]", timeInfo);
    timeBuffer[24] = 0;
    output += timeBuffer;

    output += " [";
    output += m_name;
    output += "] ";

}

void Logger::writeLogLevel(LogLevel ll, simula24::string& output)
{
    output += "[";

    if (m_sink->supportsColor())
    {
        output += m_colorMap[(int)ll];
        output += LogNameMap[(int)ll];
        output += Colors::CLEAR;
    }
    else
    {
        output += LogNameMap[(int)ll];
    }
    output += "] ";
}

void Logger::writeUserMessage(simula24::string& output, const char* message, va_list args)
{
    char temp[256] = { 0 };
    vsnprintf(temp, 256, message, args);
    output += temp;
}
