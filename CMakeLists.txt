cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(GAME_NAME "station-game")

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
project(${GAME_NAME} VERSION 0.1)

add_executable(${GAME_NAME}
    src/main/main.cpp
)

if(WIN32)
    target_include_directories(${GAME_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/thirdparty/PDCurses/"
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/include/"
    )

    target_link_libraries(${GAME_NAME}
        "${CMAKE_SOURCE_DIR}/build/pdcurses.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2main.lib"
    )

endif()