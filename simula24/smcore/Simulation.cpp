#include "Simulation.h"

#include <smcore/path/AStar.h>
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;

Simulation::Simulation() : m_objectMap(80, 60), m_CrewMembers{}
{
   
    int f = OM::getObjectTable().insert("ferrite_wall", 219, false);
    
    OM::getObjectTable().insert("hooman", 2, false);
    

}

void simula24::Simulation::update()
{
    for (auto& i : m_CrewMembers)
        i.update();
}
