#ifndef SIMULA24_TYPES_H_
#define SIMULA24_TYPES_H_

#include <stdint.h>

#ifdef _WIN32
# include <simula24/platform/windows/win32platformtypes.h>
#elif defined(__linux__) || defined(__unix__)
# include <simula24/platform/unix/unixplatformtypes.h>
#else
# error "Unknown platform!"
#endif // _Wi

namespace simula24
{

using U8 = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;

using I8 = int8_t;
using I16 = int16_t;
using I32 = int32_t;

using U64 = uint64_t;
using I64 = int64_t;

using byte = unsigned char;


}

#ifdef _MSC_VER
# define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__GNUG__)
# define FORCEINLINE __attribute__((always_inline))
#else
# pragma message("No force inline for platform")
# define FORCEINLINE inline
#endif

// make debugging easier
#ifdef SIMULA24_DEBUG
#undef FORCEINLINE
#define FORCEINLINE
#endif
#endif // SIMULA24_TYPES_H_