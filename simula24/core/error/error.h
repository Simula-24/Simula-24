#ifndef CORE_ERROR_H_
#define CORE_ERROR_H_

#include <assert.h>

#ifdef _MSC_VER
#define UNREACHABLE \
{\
printf("UNREACHABLE CODE REACHED: %s @ %s:%d\n", __FUNCSIG__, __FILE__, __LINE__);\
abort();\
}
#else
#define UNREACHABLE \
{\
printf("UNREACHABLE CODE REACHED: %s @ %s:%d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);\
abort();\
}
#endif

namespace simula24
{

enum Status
{
    OK,
    FAILED,
    ERR_FILE_OPEN,
    ERR_FILE_NOT_EXIST,
    ERR_FILE_IO,
    ERR_ACCESS_DENIED,
    ERR_INVALID_VALUE,
    ERR_INVALID_PARAMETER,
    ERR_THREAD_BUSY,
    ERR_OUT_OF_MEMORY,
    ERR_UNSPECIFIED,
    ERR_ALREADY_INITIALIZED,
    ERR_DEVICE_OR_OBJECT_FAILED_TO_CREATE,
    ERR_SYNTAX,
    ERR_LIB_INIT

};


} // simula24





#endif // CORE_ERROR_H_