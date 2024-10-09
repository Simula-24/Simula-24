#include "CrewMember.h"
using simula24::CrewMember;


CrewMember::CrewMember() :
    m_location{ 0,0 },
    m_path{},
    m_pathIndex(0),
    m_currentJob{},
    m_state(EntityState::IDLE)
{
}

CrewMember& CrewMember::operator=(const CrewMember& o)
{
    m_path = o.m_path;
    m_currentJob = o.m_currentJob;
    m_location = o.m_location;
    m_pathIndex = o.m_pathIndex;

    return *this;
}


void CrewMember::update()
{
    if (m_pathIndex < m_path.size())
    {
        m_location = m_path[m_pathIndex++];
        if (m_pathIndex >= m_path.size())
            m_state = EntityState::PERFORMING_JOB;
        return;
    }


}

void CrewMember::setPath(PointList& p)
{
    m_path = std::move(p);
    m_pathIndex = 0;
}

void CrewMember::setJob(LocalJob& j)
{
    m_currentJob = j;
    m_state = EntityState::TRAVELLING_TO_JOB;

}