#include <simula24/core/log/sink/FileSink.h>
#include <stdio.h>

using simula24::FileSink;

FileSink::FileSink(const simula24::string& filename, int flushRate)
    : FileSink(filename.c_str(), flushRate)
{
}

FileSink::FileSink(const char* filename, int flushRate)
    : m_flushRate(flushRate), m_curFlushInterval(0), m_out(nullptr)
{

    m_logCache.resize(m_flushRate);
    openFile(filename);
}

FileSink::~FileSink()
{
    if (m_out)
    {
        flush();
        fclose(m_out);
    }
    m_logCache.resize(m_curFlushInterval);
}

void FileSink::log(const simula24::string& msg)
{
    m_logCache[m_curFlushInterval] = msg;
    ++m_curFlushInterval;
    if (m_curFlushInterval >= m_flushRate)
    {
        flush();
        m_curFlushInterval = 0;
    }
}

void FileSink::flush()
{
    for (int i = 0; i < m_curFlushInterval; i++)
        fwrite(m_logCache[i].c_str(), 1, m_logCache[i].length() - 1, m_out);

    m_curFlushInterval = 0;
}

bool FileSink::openFile(const char* name)
{
    m_out = fopen(name, "a");
    return m_out != NULL;
}
