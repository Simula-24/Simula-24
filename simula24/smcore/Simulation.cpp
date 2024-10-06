#include "Simulation.h"

#include <smcore/path/AStar.h>
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;

Simulation::Simulation() : m_objectMap(80, 60), m_civilians{}
{
   
    int f = OM::getObjectTable().insert("ferrite_wall", 219, false);
    
    OM::getObjectTable().insert("hooman", 2, false);
    
    //m_objectMap.set(1, 1, f);
    //m_objectMap.set(2, 1, f);
    //m_objectMap.set(3, 1, f);
    //m_objectMap.set(4, 1, f);
    //m_objectMap.set(4, 2, f);
    //m_objectMap.set(4, 3, f);
    //m_objectMap.set(4, 4, f);
    //m_objectMap.set(3, 4, f);
    //m_objectMap.set(2, 4, f);
    //m_objectMap.set(1, 4, f);
    //m_objectMap.set(1, 3, f);
    //m_objectMap.set(1, 2, f);
    m_civilians.resize(4);
    m_civilians.push_back({});
    m_civilians.push_back({});
    m_civilians.push_back({});
    m_civilians.push_back({});
    

    stl::array<Point> startLocations;
    stl::array<Point> endLocations;
    startLocations.push_back({ 23, 45 });
    startLocations.push_back({ 5, 14 });
    startLocations.push_back({ 12, 50 });
    startLocations.push_back({ 40, 5 });

    endLocations.push_back({ 38, 45 }); // Same y-coordinate as start
    endLocations.push_back({ 25, 14 }); // Same y-coordinate as start
    endLocations.push_back({ 47, 50 }); // Same y-coordinate as start
    endLocations.push_back({ 20, 5 });

    for (int i = 0; i < 4; i++)
    {
        auto& civvie = m_civilians[i];
        civvie.setLocation(startLocations[i]);
        PointList path;
        AStarPathFind(civvie.getLocation(),endLocations[i], path, m_objectMap);
        civvie.setPath(path);
    }

}

void simula24::Simulation::update()
{
    for (auto& i : m_civilians)
        i.update();
}
