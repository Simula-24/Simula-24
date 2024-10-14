set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/memory/memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stl/string.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log/log.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log/sink/ConsoleSink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log/sink/FileSink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system/Clock.cpp

    PARENT_SCOPE
)

