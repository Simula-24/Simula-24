if(WIN32)
    message("Building for Windows")
    add_subdirectory(windows)

    set(PLATFORM_SOURCES ${WINDOWS_SOURCES} PARENT_SCOPE)

elseif(UNIX)
    message("Building for *nix")
    add_subdirectory(unix)
    set(PLATFORM_SOURCES ${UNIX_SOURCES} PARENT_SCOPE)

endif()