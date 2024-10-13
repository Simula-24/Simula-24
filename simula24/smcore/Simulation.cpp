#include "Simulation.h"

#include <smcore/path/AStar.h>
#include "job/Job.h"
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;
using simula24::LocalJob;
Simulation::Simulation() : m_station("",80, 60), m_CrewMembers{}
{
   
    OM::getObjectTable().insert("ferrite_wall", 0, false);
    
    OM::getObjectTable().insert("hooman", 1, false);
    OM::getObjectTable().insert("basic_floor", 2, true);
    
    m_CrewMembers.push_back({});
    m_CrewMembers[0].setLocation({ 15, 15 });
    LocalJob x{ .m_type = JobType::CONSTRUCT_BUILDING, .m_location = {20,20} };
    m_CrewMembers[0].setJob(x);
    AStarPathFind(m_CrewMembers[0].getLocation(), x.m_location, m_CrewMembers[0].getPath(), m_station.getObjectMap());
}


void simula24::Simulation::update()
{
    for (auto& i : m_CrewMembers)
        i.update();
}
