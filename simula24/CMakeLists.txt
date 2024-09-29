add_subdirectory(core)
add_subdirectory(platform)
add_subdirectory(game)


set(ENGINE_SOURCES 
    ${CORE_SOURCES}
    ${PLATFORM_SOURCES}
    ${GAME_SOURCES}
    PARENT_SCOPE
)

