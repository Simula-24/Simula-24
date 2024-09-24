cmake_minimum_required(VERSION 3.8)

project(pdcurses)

file(GLOB_RECURSE PDCURSES_SOURCES "${CMAKE_SOURCE_DIR}/pdcurses/*.c")
file(GLOB_RECURSE PDCURSES_SDL2_SOURCES "${CMAKE_SOURCE_DIR}/sdl2/*.c")

add_library(pdcurses SHARED
    ${PDCURSES_SOURCES}
    ${PDCURSES_SDL2_SOURCES}
)

target_include_directories(pdcurses PRIVATE 
    "${CMAKE_SOURCE_DIR}"
    "../SDL2/include/"
)


target_link_libraries(pdcurses
    "../SDL2/lib/x64/SDL2"
    "../SDL2/lib/x64/SDL2main"
)