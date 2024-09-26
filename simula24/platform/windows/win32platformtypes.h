#ifndef PLATFORM_WINDOWS_WIN32_PLATFORM_TYPES_H_
#define PLATFORM_WINDOWS_WIN32_PLATFORM_TYPES_H_

#include <windows.h>
namespace simula24
{
/// Win32 Type Aliases

using FileObject = HANDLE;
using ThreadObject = HANDLE;
using MutexObject = HANDLE;
using SemaphoreObject = HANDLE;
}

#endif // PLATFORM_WINDOWS_WIN32_PLATFORM_TYPES_H_