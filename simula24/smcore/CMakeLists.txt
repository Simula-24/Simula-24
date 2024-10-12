add_subdirectory(job)

set(SIMULATION_SOURCES
    ${JOB_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/map/ObjectMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entity/CrewMember.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path/AStar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/localsystem/LocalCluster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/station/SpaceStation.cpp
    PARENT_SCOPE
)