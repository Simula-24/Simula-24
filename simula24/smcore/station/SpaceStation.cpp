#include "SpaceStation.h"

namespace simula24 
{

SpaceStation::SpaceStation(const stl::string& name, size_t size_x, size_t size_y)
    : m_objectMap(size_x, size_y)
{
    loadDefaultMap();

}

void SpaceStation::loadDefaultMap()
{
    for (int i = 0; i < 40; i++)
    {
        m_objectMap.set(10, i + 10, 0);
        m_objectMap.set(40, i + 10, 0);
    }

    for (int i = 1; i < 30; i++)
    {
        m_objectMap.set(10 + i, 10, 0);
        m_objectMap.set(10 + i, 49, 0);
    }

    for (int i = 1; i < 30; i++)
    {
        for (int j = 1; j < 39; j++)
        {
            m_objectMap.set(10 + i, 10 + j, 2);

        }
    }
}


}