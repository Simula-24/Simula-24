#include <simula24/core/memory/memory.h>

#include <stdlib.h>

void* simula24::alloc_static(size_t size)
{
    return malloc(size);
}

void simula24::free_static(void* ptr)
{
    free(ptr);
}

void* simula24::alloc_aligned(size_t size, size_t n, size_t align)
{
    return alloc_aligned(size * n, align);
}

void* simula24::alloc_aligned(size_t size, size_t align)
{
#ifdef _MSC_VER
    return ::_aligned_malloc(size, align);
#endif
}

void simula24::free_aligned(void* ptr)
{
#ifdef _MSC_VER
    return ::_aligned_free(ptr);
#endif
}
