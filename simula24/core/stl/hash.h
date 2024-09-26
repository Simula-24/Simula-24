#ifndef SIMULA24_CORE_STL_HASH_H_
#define SIMULA24_CORE_STL_HASH_H_

#include <stdint.h>
#include "string.h"


namespace stl
{

static constexpr uint32_t HASH_PRIME = 0x01000193;
static constexpr uint32_t HASH_SEED = 0x811C9DC5;

template <class T>
class hash
{
public:
    static uint32_t run()
    {
        static_assert(false);
    }
};

/// @cond TURN_OFF_DOXYGEN
template<>
class hash<const char*>
{
public:
    static uint32_t run(const char* str, uint32_t hash)
    {
        while (*str)
            hash = run(*str++, hash);
        return hash;
    }
    static  uint32_t run(unsigned char c, uint32_t hash)
    {
        return (c ^ hash) * HASH_PRIME;
    }
};
template<>
class hash<string>
{
public:
    static uint32_t run(const string& str, uint32_t hash = HASH_SEED)
    {
        return simula24::hash<const char*>::run(str.c_str(), hash);
    }
};
template<>
class hash<uint32_t>
{
public:
    static uint32_t run(uint32_t v, uint32_t hash = HASH_SEED)
    {
        uint8_t* ptr = (uint8_t*)&v;
        hash = (ptr[3] ^ hash) * HASH_PRIME;
        hash = (ptr[2] ^ hash) * HASH_PRIME;
        hash = (ptr[1] ^ hash) * HASH_PRIME;
        hash = (ptr[0] ^ hash) * HASH_PRIME;
        return hash;
    }
};
template<>
class hash<uint64_t>
{
public:
    static uint32_t run(uint64_t v, uint32_t hash = HASH_SEED)
    {
        uint8_t* ptr = (uint8_t*)&v;
        hash = (ptr[7] ^ hash) * HASH_PRIME;
        hash = (ptr[6] ^ hash) * HASH_PRIME;
        hash = (ptr[5] ^ hash) * HASH_PRIME;
        hash = (ptr[4] ^ hash) * HASH_PRIME;
        hash = (ptr[3] ^ hash) * HASH_PRIME;
        hash = (ptr[2] ^ hash) * HASH_PRIME;
        hash = (ptr[1] ^ hash) * HASH_PRIME;
        hash = (ptr[0] ^ hash) * HASH_PRIME;
        return hash;
    }
};
template<>
class hash<int>
{
public:
    static uint32_t run(int v, uint32_t hash = HASH_SEED)
    {
        return simula24::hash<uint32_t>::run((uint32_t)v, hash);
    }
};

/// @endcond

} // simula24

#endif // SIMULA24_CORE_STL_HASH_H_