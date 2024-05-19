set(TARGET_NAME "nm_prof")

file(GLOB_RECURSE SRCS "*.[c|h]pp")

add_library(${TARGET_NAME} STATIC ${SRCS})
add_library(nm::prof ALIAS ${TARGET_NAME})

target_link_libraries(${TARGET_NAME} PRIVATE 
    nm::logger
)

target_include_directories(${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)