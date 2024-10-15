#include "LocalCluster.h"
#include <random>

using simula24::LocalCluster;
using simula24::Point;

LocalCluster::LocalCluster(const stl::string& name, int numStarSystems)
{
    m_clusterName = name;
    
    generateStarSystems(numStarSystems);
    generateBackgroundStars();

}

void LocalCluster::generateStarSystems(int num)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, 2000);
    m_starSystems.resize(num);
    for (int i = 0; i < num; i++)
    {
        m_starSystems.insert({  
            {
                dist(rng),
                dist(rng),
            },
            5
        });
    }

}

void LocalCluster::generateBackgroundStars()
{

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, 2000);

    m_randomStars.resize(1000);
    for (int i = 0; i < 1000; i++)
        m_randomStars.push_back({
            dist(rng),
            dist(rng),
        });
}
