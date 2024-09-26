#include <simula24/core/error/seh.h>

#include <Windows.h>
#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp.lib")

static LONG WINAPI CreateMiniDump(EXCEPTION_POINTERS*);

void simula24::setSEHHandler()
{
    SetUnhandledExceptionFilter(CreateMiniDump);
}

LONG WINAPI CreateMiniDump(EXCEPTION_POINTERS* ep)
{
    HANDLE dumpfile = CreateFile(
        "minidump.dmp",
        GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (dumpfile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION dInfo =
        {
            .ThreadId = GetCurrentThreadId(),
            .ExceptionPointers = ep,
            .ClientPointers = TRUE
        };

        MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            dumpfile,
            (MINIDUMP_TYPE)(
                MiniDumpWithHandleData |
                MiniDumpWithDataSegs |
                MiniDumpWithThreadInfo |
                MiniDumpWithFullMemory
                ),
            &dInfo,
            NULL,
            NULL
        );
        CloseHandle(dumpfile);
    }
    return EXCEPTION_EXECUTE_HANDLER;

}

