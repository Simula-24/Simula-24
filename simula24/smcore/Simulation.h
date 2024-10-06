#ifndef SMCORE_SIMULATION_H_
#define SMCORE_SIMULATION_H_

#include <core/stl/array.h>
#include <smcore/entity/Civilian.h>
#include <smcore/map/ObjectMap.h>
namespace simula24
{

///
/// @brief
///     Our actual game class
///     This manages the map + civilians
/// 
class Simulation
{
public:
    Simulation();

    const ObjectMap& getObjectMap() const { return m_objectMap; }
    const stl::array<Civilian>& getCivilianList() const { return m_civilians; }
    void update();

private:
    stl::array<Civilian> m_civilians;
    stl::array<Point> m_path;
    size_t m_pathIndex;
    ObjectMap m_objectMap;
};

}


#endif // SMCORE_SIMULATION_H_