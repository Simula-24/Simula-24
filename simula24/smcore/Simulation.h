#ifndef SMCORE_SIMULATION_H_
#define SMCORE_SIMULATION_H_

#include <core/stl/array.h>
#include <smcore/station/SpaceStation.h>
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

    ObjectMap& getObjectMap() { return m_station.getObjectMap(); }
    const stl::array<CrewMember>& getCrewMemberList() const { return m_CrewMembers; }
    void update();

private:
    stl::array<CrewMember> m_CrewMembers;
    SpaceStation m_station;
};

}


#endif // SMCORE_SIMULATION_H_