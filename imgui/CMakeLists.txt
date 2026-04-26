file(GLOB IMGUI_CPPS *.cpp)

add_library(imgui_cpp STATIC ${IMGUI_CPPS})

target_include_directories(imgui_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(imgui_cpp PRIVATE Vulkan::Vulkan)