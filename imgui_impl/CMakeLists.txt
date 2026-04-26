file(GLOB IMGUI_IMPL_CPPS *.cpp)

add_library(imgui_impl_cpp STATIC ${IMGUI_IMPL_CPPS})

target_include_directories(imgui_impl_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(imgui_impl_cpp PRIVATE Vulkan::Vulkan)