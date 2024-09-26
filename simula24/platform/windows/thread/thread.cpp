#include <core/thread/thread.h>
#include <core/types.h>

#include <Windows.h>

using simula24::thread;
using simula24::ThreadObject;

void thread::start(void* function, void* args)
{
    DWORD tid;
    m_thread = CreateThread(
        NULL,
        0,
        static_cast<LPTHREAD_START_ROUTINE>(function),
        args,
        0,
        &tid
    );

    m_id = static_cast<size_t>(tid);

}

void thread::join()
{
    if (m_thread)
    {
        WaitForSingleObject(m_thread, INFINITE);
        CloseHandle(m_thread);
    }
}

size_t thread::getId() const
{
    return static_cast<size_t>(GetThreadId(m_thread));
}

size_t thread::getThreadID()
{
    return static_cast<size_t>(GetCurrentThreadId());
}