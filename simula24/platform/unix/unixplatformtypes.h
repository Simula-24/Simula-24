#ifndef PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_
#define PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

namespace simula24
{

using FileObject = FILE*;
using ThreadObject = pthread_t;
using MutexObject = pthread_mutex_t;
using SemaphoreObject = sem_t;
}

#endif // PLATFORM_UNIX_UNIX_PLATFORM_TYPES_H_