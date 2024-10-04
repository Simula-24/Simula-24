#ifndef SMCORE_SIMULATION_H_
#define SMCORE_SIMULATION_H_

#include <core/stl/array.h>
#include <smcore/entity/Civilian.h>
#include <smcore/map/ObjectMap.h>
namespace simula24
{

class Simulation
{
public:
    Simulation();
    const ObjectMap& getObjectMap() const { return m_objectMap; }

private:
    Civilian m_civvie;
    stl::array<Point> m_path;
    size_t m_pathIndex;
    ObjectMap m_objectMap;
};

}


#endif // SMCORE_SIMULATION_H_