add_subdirectory(tile)

set(GAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/object/ObjectTable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    ${TILE_SOURCES}
    PARENT_SCOPE
)