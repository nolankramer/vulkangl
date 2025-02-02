cmake_minimum_required(VERSION 3.19)

set(vulkangl_known_comps static shared)
set(vulkangl_comp_static NO)
set(vulkangl_comp_shared NO)
foreach (vulkangl_comp IN LISTS ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
    if (vulkangl_comp IN_LIST vulkangl_known_comps)
        set(vulkangl_comp_${vulkangl_comp} YES)
    else ()
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
            "vulkangl does not recognize component `${vulkangl_comp}`.")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
        return()
    endif ()
endforeach ()

if (vulkangl_comp_static AND vulkangl_comp_shared)
    set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
        "vulkangl `static` and `shared` components are mutually exclusive.")
    set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
    return()
endif ()

set(vulkangl_static_targets "${CMAKE_CURRENT_LIST_DIR}/vulkangl-static-targets.cmake")
set(vulkangl_shared_targets "${CMAKE_CURRENT_LIST_DIR}/vulkangl-shared-targets.cmake")

macro(vulkangl_load_targets type)
    if (NOT EXISTS "${vulkangl_${type}_targets}")
        set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE
            "vulkangl `${type}` libraries were requested but not found.")
        set(${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
        return()
    endif ()
    include("${vulkangl_${type}_targets}")
endmacro()

if (vulkangl_comp_static)
    vulkangl_load_targets(static)
elseif (vulkangl_comp_shared)
    vulkangl_load_targets(shared)
elseif (DEFINED vulkangl_SHARED_LIBS AND vulkangl_SHARED_LIBS)
    vulkangl_load_targets(shared)
elseif (DEFINED vulkangl_SHARED_LIBS AND NOT vulkangl_SHARED_LIBS)
    vulkangl_load_targets(static)
elseif (BUILD_SHARED_LIBS)
    if (EXISTS "${vulkangl_shared_targets}")
        vulkangl_load_targets(shared)
    else ()
        vulkangl_load_targets(static)
    endif ()
else ()
    if (EXISTS "${vulkangl_static_targets}")
        vulkangl_load_targets(static)
    else ()
        vulkangl_load_targets(shared)
    endif ()
endif ()