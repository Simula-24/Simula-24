#include <simula24/core/io/file.h>
#include <simula24/core/error/error.h>

#include <windows.h>
#include <fileapi.h>
///
/// @brief
///     Windows-Specific File operations
/// 

using simula24::File;
using simula24::Status;

File::File()
    : m_isOpen(false), m_file(INVALID_HANDLE_VALUE)
{
}

File::~File()
{
    if (m_isOpen)
        close();
}


Status File::open(const char* filename, AccessMode mode)
{
    DWORD access = 0;
    DWORD createPolicy = 0;

    switch (mode)
    {
        case READ:
            access = GENERIC_READ;
            createPolicy = OPEN_EXISTING;
            break;
        case WRITE:
            access = GENERIC_WRITE;
            createPolicy = CREATE_ALWAYS;
            break;
        case READ_WRITE:
        case WRITE_READ:
            access = GENERIC_READ | GENERIC_WRITE;
            createPolicy = CREATE_ALWAYS;
            break;
        case APPEND:
        case READ_APPEND:
            access = FILE_APPEND_DATA;
            createPolicy = CREATE_ALWAYS;
            break;
        default:
            return ERR_INVALID_PARAMETER;
    }

    m_file = CreateFileA(
        filename,
        access,
        FILE_SHARE_READ,
        NULL,
        createPolicy,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    DWORD err = GetLastError();
    Status retStat = OK;

    if (err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND)
        retStat = ERR_FILE_NOT_EXIST;

    else if (err == ERROR_FILE_EXISTS || err == ERROR_ALREADY_EXISTS || err == ERROR_SUCCESS)
    {
        m_isOpen = true;
        retStat = OK;
    }
    m_amode = mode;
    return retStat;
}

void File::close()
{
    if (m_isOpen)
        return;

    CloseHandle(m_file);
    m_file = INVALID_HANDLE_VALUE;
    m_isOpen = false;
}



size_t File::getSize() const
{
    assert(m_isOpen == true);
    return (size_t)GetFileSize(m_file, NULL);
}

Status File::read(void* out, size_t _sz_of_1, size_t n, size_t* bytesRead)
{
    assert(m_isOpen && m_amode != WRITE && m_amode != APPEND);
    return read(out, _sz_of_1 * n, bytesRead);
}

Status File::read(void* out, size_t numBytes, size_t* bytesRead)
{
    assert(m_isOpen && m_amode != WRITE && m_amode != APPEND);
    DWORD discarded = 0;

    BOOL stats = ReadFile(
        m_file, out, static_cast<DWORD>(numBytes), &discarded, NULL
    );

    if (bytesRead)
        *bytesRead = static_cast<size_t>(discarded);

    if (stats != ERROR_SUCCESS)
        return ERR_UNSPECIFIED;

    return OK;
}

Status File::write(const void* in, size_t numBytes, size_t* bytesWritten)
{
    assert(m_isOpen && m_amode != READ);
    DWORD br;

    BOOL writeStatus = WriteFile(
        m_file, in, static_cast<DWORD>(numBytes), &br, NULL
    );

    if (bytesWritten)
        *bytesWritten = (size_t)br;

    if (writeStatus != ERROR_SUCCESS)
        return ERR_UNSPECIFIED;

    return OK;

}

Status File::write(const void* in, size_t _szof_1, size_t n, size_t* bytesWritten)
{
    assert(m_isOpen && m_amode != READ);

    return write(in, _szof_1 * n, bytesWritten);
}