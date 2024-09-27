cmake_minimum_required(VERSION 3.8)

project(pdcurses)

file(GLOB_RECURSE PDCURSES_SOURCES "${CMAKE_SOURCE_DIR}/pdcurses/*.c")
file(GLOB_RECURSE PDCURSES_SDL2_SOURCES "${CMAKE_SOURCE_DIR}/sdl2/*.c")

set(RUNTIME_OUTPUT_DIRECTORY "Debug")
set(ARCHIVE_OUTPUT_DIRECTORY "Debug")

add_library(pdcurses STATIC
    ${PDCURSES_SOURCES}
    ${PDCURSES_SDL2_SOURCES}
)
target_compile_definitions(pdcurses PRIVATE PDC_WIDE=1)

target_include_directories(pdcurses PRIVATE 
    "${CMAKE_SOURCE_DIR}"
    "../SDL2/include/"
    "../SDL2_ttf/include/"
)


target_link_libraries(pdcurses
    "../SDL2/lib/x64/SDL2"
    "../SDL2/lib/x64/SDL2main"
    "../SDL2_ttf/lib/x64/SDL2_ttf"
)

