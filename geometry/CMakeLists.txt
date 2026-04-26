file(GLOB GEOMETRY_CPPS *.cpp)

add_library(geometry_cpp STATIC ${GEOMETRY_CPPS})

target_include_directories(geometry_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(geometry_cpp PRIVATE Vulkan::Vulkan)