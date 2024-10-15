#ifndef SIMULA24_CORE_MEMORY_MEMORY_H_
#define SIMULA24_CORE_MEMORY_MEMORY_H_
#include <stddef.h>


namespace simula24
{


void* alloc_static(size_t size);
void  free_static(void* ptr);

void* alloc_aligned(size_t size, size_t n, size_t align);
void* alloc_aligned(size_t size, size_t align);
void  free_aligned(void* ptr);
} // simula24

#endif // SIMULA24_CORE_MEMORY_MEMORY_H_