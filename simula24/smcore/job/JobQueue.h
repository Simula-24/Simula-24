#ifndef SMCORE_JOB_QUEUE_H_
#define SMCORE_JOB_QUEUE_H_

// TODO: custom implementation + priorities
#include <queue>
#include <optional>
#include "Job.h"

namespace simula24
{
    
class JobQueue
{
public:

    JobQueue();

    void addNewJob(const LocalJob&);
    std::optional<LocalJob> getJob();



private:
    std::queue<LocalJob> m_jqueue;
};


} // simula24



#endif // SMCORE_JOB_QUEUE_H_