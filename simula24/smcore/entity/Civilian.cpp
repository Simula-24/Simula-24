#include "Civilian.h"

using simula24::Civilian;

void Civilian::update()
{
    if (m_pathIndex < m_path.size())
    {
        m_location = m_path[m_pathIndex++];
    }

}