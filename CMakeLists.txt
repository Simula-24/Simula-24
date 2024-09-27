cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

project(simula24 VERSION 0.1)

option(ENABLE_TESTS "Enable Tests" OFF)

set(SIMULA24_LIBRARIES)

if(ENABLE_TESTS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/test/")
    add_subdirectory("tests")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
    add_subdirectory("simula24/main/")
endif()

add_subdirectory("simula24")
add_executable(simula24
    ${MAIN_SOURCES}
    ${ENGINE_SOURCES}
)

if(WIN32)
    target_include_directories(simula24 PRIVATE
        "${CMAKE_SOURCE_DIR}/thirdparty/PDCurses/"
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/include/"
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2_ttf/include/"
    )

    set(SIMULA24_LIBRARIES ${SIMULA24_LIBRARIES}
        "${CMAKE_SOURCE_DIR}/build/pdcurses.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2_ttf.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2main.lib"
    )
    add_compile_options("/wd9025")
elseif(UNIX)
    find_package(SDL2 REQUIRED)
    target_include_directories(simula24 PRIVATE ${SDL2_INCLUDE_DIRS})
    set(SIMULA24_LIBRARIES ${SIMULA24_LIBRARIES} ${SDL2_LIBRARIES} "ncursesw")

endif()



if(ENABLE_TESTS)
    set(SIMULA24_LIBRARIES ${SIMULA24_LIBRARIES} PUBLIC GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(simula24)
endif()


target_link_libraries(simula24 PRIVATE ${SIMULA24_LIBRARIES})
target_include_directories(simula24 PUBLIC 
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/simula24/"
)