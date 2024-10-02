add_subdirectory(tile)

set(GAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/object/ObjectTable.cpp
    ${TILE_SOURCES}
    PARENT_SCOPE
)