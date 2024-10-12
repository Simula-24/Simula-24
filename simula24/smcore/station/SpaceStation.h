#ifndef SMCORE_STATION_SPACESTATION_H_
#define SMCORE_STATION_SPACESTATION_H_

#include <smcore/map/ObjectMap.h>

namespace simula24
{


///
/// @brief
///     Space Station - where all the action happens
/// 
class SpaceStation
{
public:

    

    const ObjectMap& getObjectMap() const { return m_objectMap; }

private:
    ObjectMap m_objectMap;
};

} // simula24


#endif // SMCORE_STATION_SPACESTATION_H_