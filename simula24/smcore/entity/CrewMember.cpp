#include "CrewMember.h"

using simula24::CrewMember;

void CrewMember::update()
{
    if (m_pathIndex < m_path.size())
    {
        m_location = m_path[m_pathIndex++];
    }

}