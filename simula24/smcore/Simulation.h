#ifndef SMCORE_SIMULATION_H_
#define SMCORE_SIMULATION_H_

#include <core/stl/array.h>
#include <smcore/entity/CrewMember.h>
#include <smcore/map/ObjectMap.h>
namespace simula24
{

///
/// @brief
///     Our actual game class
///     This manages the map + CrewMembers
/// 
class Simulation
{
public:
    Simulation();

    const ObjectMap& getObjectMap() const { return m_objectMap; }
    const stl::array<CrewMember>& getCrewMemberList() const { return m_CrewMembers; }
    void update();

private:
    stl::array<CrewMember> m_CrewMembers;
    stl::array<Point> m_path;
    size_t m_pathIndex;
    ObjectMap m_objectMap;
};

}


#endif // SMCORE_SIMULATION_H_