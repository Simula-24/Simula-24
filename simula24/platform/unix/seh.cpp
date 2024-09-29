#include <core/error/seh.h>
#include <core/log/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>

void simula24::setSEHHandler()
{
    // local version of `ulimit -c unlimited`
    // This will ensure if there is a crash,
    // the core will be dumped
    struct rlimit proc_core_limit;

    proc_core_limit.rlim_cur = RLIM_INFINITY;
    proc_core_limit.rlim_max = RLIM_INFINITY;

    if (setrlimit(RLIMIT_CORE, &proc_core_limit) != 0)
    {
        ENGINE_ERROR("Failed to set RLIMIT_CORE. Crashes may not core dump");
    }

}