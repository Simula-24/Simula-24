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

private:
    stl::array<Civilian> m_civlist;
    ObjectMap m_objectMap;
};

}


#endif // SMCORE_SIMULATION_H_