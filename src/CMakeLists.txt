set(VULKANGL_HDRS_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE VULKANGL_HDRS "${VULKANGL_HDRS_DIR}/*.h" "{VULKANGL_HDRS_DIR}/*.hpp")
file(GLOB_RECURSE VULKANGL_SRC "*.c" "*.cpp")

add_library(vulkangl)
add_library(vulkangl::vulkangl ALIAS vulkangl)

set_target_properties(vulkangl PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
)

target_include_directories(vulkangl
    PUBLIC
        "$<BUILD_INTERFACE:${VULKANGL_HDRS_DIR}>"
)

target_sources(vulkangl PRIVATE ${VULKANGL_SRC})

target_compile_features(vulkangl PUBLIC cxx_std_17)

include(GenerateExportHeader)
generate_export_header(vulkangl EXPORT_FILE_NAME "${VULKANGL_HDRS_DIR}/vulkangl/api.h")
target_compile_definitions(
    vulkangl PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:VULKANGL_STATIC_DEFINE>")
target_include_directories(
    vulkangl PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

