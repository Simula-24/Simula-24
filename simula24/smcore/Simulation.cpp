#include "Simulation.h"

#include <smcore/path/AStar.h>
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;

Simulation::Simulation() : m_objectMap(80, 60)
{
    m_civvie.setLocation({ 0,0 });
    m_pathIndex = 0;
    int f = OM::getObjectTable().insert("ferrite_wall", 219, false);
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
    AStarPathFind(m_civvie.getLocation(), { 50,40 }, m_path, m_objectMap);
}