add_subdirectory(core)
add_subdirectory(platform)


set(ENGINE_SOURCES 
    ${CORE_SOURCES}
    ${PLATFORM_SOURCES}
    PARENT_SCOPE
)

