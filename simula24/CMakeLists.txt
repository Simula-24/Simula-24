add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(platform)
add_subdirectory(graphics)
add_subdirectory(objectmanager)
#add_subdirectory(smcore)


set(ENGINE_SOURCES 
    ${CORE_SOURCES}
    ${MATH_SOURCES}
    ${PLATFORM_SOURCES}
    ${GRAPHICS_SOURCES}
    ${OBJECT_MANAGER_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    PARENT_SCOPE
)

