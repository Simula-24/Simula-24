#include "Simulation.h"

#include <smcore/path/AStar.h>
#include "job/Job.h"
#include <graphics/tile/TileSize.h>
#include <objectmanager/ObjectManager.h>
using simula24::Simulation;
using simula24::LocalJob;
Simulation::Simulation() : m_station("",80, 60), m_CrewMembers{}
{
   
    OM::getObjectTable().insert("ferrite_wall", 0, false, TileSize::MEDIUM);
    OM::getObjectTable().insert("hooman", 1, false, TileSize::FLAT);
    OM::getObjectTable().insert("basic_floor", 2, true, TileSize::FLAT);
    
    m_CrewMembers.push_back({});
    m_CrewMembers[0].setLocation({ 15, 15 });
    LocalJob x{ .m_type = JobType::CONSTRUCT_BUILDING, .m_location = {20,20} };
    AStarPathFind(m_CrewMembers[0].getLocation(), x.m_location, m_CrewMembers[0].getPath(), m_station.getObjectMap());
    m_CrewMembers[0].setJob(x);
}


void simula24::Simulation::update()
{
    for (auto& i : m_CrewMembers)
    {
        i.update();
        if (i.getCurrentState() == EntityState::PERFORMING_JOB)
        {
            m_station.submitWork(i.getJob());
        }
    }
}
