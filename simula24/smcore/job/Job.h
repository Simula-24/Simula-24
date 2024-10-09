#ifndef SMCORE_JOB_JOBQUEUE_H_
#define SMCORE_JOB_JOBQUEUE_H_

#include "JobType.h"
#include <math/Point.h>

namespace simula24
{

struct LocalJob
{
    JobType m_type;
    Point   m_location;
};


} // simula24


#endif // SMCORE_JOB_JOBQUEUE_H_