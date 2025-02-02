include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (NOT DEFINED vulkangl_INSTALL_CMAKEDIR)
   set(vulkangl_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/vulkangl"
       CACHE STRING "Path to vulkangl CMake files")
endif ()

install(TARGETS vulkangl EXPORT vulkangl_Targets
        RUNTIME COMPONENT vulkangl_Runtime
        LIBRARY COMPONENT vulkangl_Runtime
        NAMELINK_COMPONENT vulkangl_Development
        ARCHIVE COMPONENT vulkangl_Development
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(DIRECTORY "${vulkangl_SOURCE_DIR}/include/" "${vulkangl_BINARY_DIR}/include/"
        TYPE INCLUDE
        COMPONENT vulkangl_Development)

if (BUILD_SHARED_LIBS)
    set(type shared)
else ()
    set(type static)
endif ()

install(EXPORT vulkangl_Targets
        DESTINATION "${vulkangl_INSTALL_CMAKEDIR}"
        NAMESPACE vulkangl::
        FILE vulkangl-${type}-targets.cmake
        COMPONENT vulkangl_Development)

write_basic_package_version_file(
    vulkanglConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/vulkanglConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/vulkanglConfigVersion.cmake"
        DESTINATION "${vulkangl_INSTALL_CMAKEDIR}"
        COMPONENT vulkangl_Development)

# TODO: add additional CPack variables here
include(CPack)
