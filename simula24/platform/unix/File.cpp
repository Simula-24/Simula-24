#include <core/io/file.h>
#include <core/error/error.h>
#include <stdio.h>
#include <unistd.h>

using simula24::File;
using simula24::Status;

File::File()
    : m_isOpen(false), m_file(nullptr)
{
}

File::~File()
{
    if (m_isOpen)
        close();
}

Status File::open(const char* filename, AccessMode mode)
{
    const char* openmode = nullptr;

    switch (mode)
    {
        case READ:
            openmode = "rb";
            break;
        case WRITE:
            openmode = "wb";
            break;
        case READ_WRITE:
            openmode = "rb+";
            break;
        case WRITE_READ:
            openmode = "wb+";
            break;
        case APPEND:
            openmode = "a";
            break;
        case READ_APPEND:
            openmode = "a+";
            break;
        default:
            return ERR_INVALID_PARAMETER;
    }

    m_file = fopen(filename, openmode);

    if (!m_file)
        return ERR_FILE_IO;

    m_isOpen = true;
    return OK;
}

void File::close()
{
    if (m_isOpen && m_file)
    {
        fclose(m_file);
        m_file = nullptr;
        m_isOpen = false;
    }
}

size_t File::getSize() const
{
    assert(m_isOpen == true);
}

Status File::read(void* out, size_t _sz_of_1, size_t n, size_t* bytesRead)
{
    assert(m_isOpen && m_amode != WRITE && m_amode != APPEND);

    size_t bytes = fread(out, _sz_of_1, n, m_file);

    if (bytes == 0)
    {
        *bytesRead = 0;
        return ERR_FILE_IO;
    }

    if (bytesRead)
        *bytesRead = bytes;

    return OK;
}

Status File::read(void* out, size_t numBytes, size_t* bytesRead)
{
    assert(m_isOpen && m_amode != WRITE && m_amode != APPEND);

    size_t bytes = fread(out, 1, numBytes, m_file);

    if (bytes == 0)
    {
        *bytesRead = 0;
        return ERR_FILE_IO;
    }
    if(bytesRead)
        *bytesRead = bytes;

    return OK;
}

Status File::write(const void* in, size_t numBytes, size_t* bytesWritten)
{
    assert(m_isOpen && m_amode != READ);

    size_t bytes = fwrite(in, 1, numBytes, m_file);

    if (bytes == 0)
    {
        *bytesWritten = 0;
        return ERR_FILE_IO;
    }
    if (bytesWritten)
        *bytesWritten = bytes;

    return OK;

}

Status File::write(const void* in, size_t _szof_1, size_t n, size_t* bytesWritten)
{
    assert(m_isOpen && m_amode != READ);


    size_t bytes = fwrite(in, _szof_1, n, m_file);

    if (bytes == 0)
    {
        *bytesWritten = 0;
        return ERR_FILE_IO;
    }
    if (bytesWritten)
        *bytesWritten = bytes;

    return OK;

}