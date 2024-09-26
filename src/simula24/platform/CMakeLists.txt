if(WIN32)
    message("Building for Windows")
    add_subdirectory(windows)

    set(PLATFORM_SOURCES ${WINDOWS_SOURCES} PARENT_SCOPE)

endif()