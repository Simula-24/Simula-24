#ifndef SMCORE_LOCAL_SYSTEM_LOCAL_CLUSTER_H_
#define SMCORE_LOCAL_SYSTEM_LOCAL_CLUSTER_H_

#include <core/stl/string.h>
#include <core/stl/unordered_map.h>
#include <math/Point.h>

namespace simula24
{

class LocalCluster
{
public:
    LocalCluster(const stl::string& name, int numStarSystems);

    auto& getStarSystemMap() { return m_starSystems; }
    auto& getRandomStarMap() { return m_randomStars; }
private:
   
    void generateStarSystems(int num);
    
    void generateBackgroundStars();

    stl::string m_clusterName;

    stl::unordered_map<Point, int> m_starSystems;
    
    // random stars for the background
    stl::array<Point> m_randomStars;

};

} // simula24


#endif // SMCORE_LOCAL_SYSTEM_LOCAL_CLUSTER_H_