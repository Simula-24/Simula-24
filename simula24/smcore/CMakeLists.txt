add_subdirectory(job)

set(SIMULATION_SOURCES
    ${JOB_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Simulation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/map/ObjectMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/entity/CrewMember.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/path/AStar.cpp

    PARENT_SCOPE
)