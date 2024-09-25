cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

project(miri_game VERSION 0.1)

option(ENABLE_TESTS "Enable Tests" OFF)

set(MIRI_LIBRARIES)

if(ENABLE_TESTS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/test/")
    add_subdirectory("tests")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
    add_subdirectory("src/main/")
endif()

add_subdirectory(src)
add_executable(miri_game
    ${MAIN_SOURCES}
    ${ENGINE_SOURCES}
)

if(WIN32)
    target_include_directories(miri_game PRIVATE
        "${CMAKE_SOURCE_DIR}/thirdparty/PDCurses/"
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/include/"
    )

    set(MIRI_LIBRARIES ${MIRI_LIBRARIES}
        "${CMAKE_SOURCE_DIR}/build/pdcurses.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2.lib"
        "${CMAKE_SOURCE_DIR}/build/SDL2main.lib"
    )

endif()



if(ENABLE_TESTS)
    set(MIRI_LIBRARIES ${MIRI_LIBRARIES} PUBLIC GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(miri_game)
endif()


target_link_libraries(miri_game PRIVATE ${MIRI_LIBRARIES})
target_include_directories(miri_game PUBLIC "${CMAKE_SOURCE_DIR}/src")