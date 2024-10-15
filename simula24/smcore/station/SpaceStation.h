#ifndef SMCORE_STATION_SPACESTATION_H_
#define SMCORE_STATION_SPACESTATION_H_

#include <smcore/map/ObjectMap.h>

namespace simula24
{
class LocalJob;

///
/// @brief
///     Space Station - where all the action happens
/// 
class SpaceStation
{
public:

    SpaceStation(const stl::string& name, size_t size_x, size_t size_y);

    const ObjectMap& getObjectMap() const { return m_objectMap; }
    void submitWork(const LocalJob&);
private:
    
    void loadDefaultMap();

    ObjectMap m_objectMap;
};

} // simula24


#endif // SMCORE_STATION_SPACESTATION_H_