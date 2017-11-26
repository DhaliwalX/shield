if (FONTCONFIG_LIBRARIES AND FONTCONFIG_INCLUDE_DIR)

    # in cache already
    set(FONTCONFIG_FOUND TRUE)

else (FONTCONFIG_LIBRARIES AND FONTCONFIG_INCLUDE_DIR)

    if (NOT WIN32)
        # use pkg-config to get the directories and then use these values
        # in the FIND_PATH() and FIND_LIBRARY() calls
        find_package(PkgConfig)
        pkg_check_modules(PC_FONTCONFIG fontconfig)

        set(FONTCONFIG_DEFINITIONS ${PC_FONTCONFIG_CFLAGS_OTHER})
    endif (NOT WIN32)

    find_path(FONTCONFIG_INCLUDE_DIR fontconfig/fontconfig.h
            PATHS
            ${PC_FONTCONFIG_INCLUDEDIR}
            ${PC_FONTCONFIG_INCLUDE_DIRS}
            /usr/X11/include
            )

    find_library(FONTCONFIG_LIBRARIES NAMES fontconfig
            PATHS
            ${PC_FONTCONFIG_LIBDIR}
            ${PC_FONTCONFIG_LIBRARY_DIRS}
            )

    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(Fontconfig DEFAULT_MSG FONTCONFIG_LIBRARIES FONTCONFIG_INCLUDE_DIR )

    mark_as_advanced(FONTCONFIG_LIBRARIES FONTCONFIG_INCLUDE_DIR)

endif (FONTCONFIG_LIBRARIES AND FONTCONFIG_INCLUDE_DIR)
