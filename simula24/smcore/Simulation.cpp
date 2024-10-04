#include "Simulation.h"

#include <smcore/path/AStar.h>
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;

Simulation::Simulation() : m_objectMap(80, 60)
{
    m_civvie.setLocation({ 1,1 });
    m_pathIndex = 0;
    int f = OM::getObjectTable().insert("ferrite_wall", 219, false);
    OM::getObjectTable().insert("hooman", 1, false);
    m_objectMap.set(1, 1, f);
    m_objectMap.set(2, 1, f);
    m_objectMap.set(3, 1, f);
    m_objectMap.set(4, 1, f);
    m_objectMap.set(4, 2, f);
    m_objectMap.set(4, 3, f);
    m_objectMap.set(4, 4, f);
    m_objectMap.set(3, 4, f);
    m_objectMap.set(2, 4, f);
    m_objectMap.set(1, 4, f);
    m_objectMap.set(1, 3, f);
    m_objectMap.set(1, 2, f);
    AStarPathFind(m_civvie.getLocation(), { 20,20 }, m_path, m_objectMap);
}

void simula24::Simulation::update()
{
    if (m_pathIndex >= m_path.size()) return;
    if (m_pathIndex > 0)
        m_objectMap.set(m_path[m_pathIndex - 1].x, m_path[m_pathIndex - 1].y, -1);
    Point i = m_path[m_pathIndex++];
    m_objectMap.set(i.x, i.y, 1);
}
