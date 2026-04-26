file(GLOB VULKAN_CPPS *.cpp)

add_library(vulkan_cpp STATIC ${VULKAN_CPPS})

target_include_directories(vulkan_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(vulkan_cpp PRIVATE Vulkan::Vulkan)