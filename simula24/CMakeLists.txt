add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(platform)
add_subdirectory(graphics)
add_subdirectory(app)
#add_subdirectory(smcore)


set(ENGINE_SOURCES 
    ${CORE_SOURCES}
    ${MATH_SOURCES}
    ${PLATFORM_SOURCES}
    ${GRAPHICS_SOURCES}
    ${GAME_SOURCES}
    PARENT_SCOPE
)

