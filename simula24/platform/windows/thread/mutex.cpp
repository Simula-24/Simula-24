#include <platform/windows/win32platformtypes.h>
#include <core/error/error.h>
#include <core/thread/mutex.h>

#include <synchapi.h>

using simula24::Mutex;
using simula24::Status;


Mutex::Mutex()
    : m_mtx(nullptr)
{
}

Mutex::~Mutex()
{
    if (m_mtx)
        destroy();
}


Status Mutex::create()
{
    m_mtx = CreateMutex(
        NULL,
        FALSE,
        NULL
    );

    if (m_mtx != NULL)
        return OK;

    auto err = GetLastError();

    switch (err)
    {
        case ERROR_ACCESS_DENIED:
            return ERR_ACCESS_DENIED;
        case ERROR_INVALID_HANDLE:
            return ERR_INVALID_PARAMETER;
        case ERROR_NOT_ENOUGH_MEMORY:
            return ERR_OUT_OF_MEMORY;
        default:
            return ERR_UNSPECIFIED;
    }
}

void Mutex::destroy()
{
    if (m_mtx)
    {
        CloseHandle(m_mtx);
        m_mtx = nullptr;
    }
}

void Mutex::lock()
{
    // TODO: find better values
    WaitForSingleObject(m_mtx, INFINITE);
}

void Mutex::unlock()
{
    ReleaseMutex(m_mtx);
}