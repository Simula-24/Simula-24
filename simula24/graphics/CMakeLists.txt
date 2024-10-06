add_subdirectory(tile)

set(GRAPHICS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/AppWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AppWindowMgr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer/RenderManager.cpp
    ${TILE_SOURCES}

    PARENT_SCOPE
)