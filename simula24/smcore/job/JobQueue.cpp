#include "JobQueue.h"

using simula24::JobQueue;
using simula24::LocalJob;

JobQueue::JobQueue() : m_jqueue{} {}

void JobQueue::addNewJob(const LocalJob& lj)
{
    m_jqueue.push(lj);
}

std::optional<LocalJob> JobQueue::getJob()
{
    if (m_jqueue.empty())
        return std::nullopt;
    LocalJob& j = m_jqueue.front();
    m_jqueue.pop();
    return j;

}