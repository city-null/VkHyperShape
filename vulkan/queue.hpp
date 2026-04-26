#ifndef VULKAN_QUEUE_HPP
#define VULKAN_QUEUE_HPP
#include <array>
#include "device.hpp"
namespace vulkan{
    struct Queue{
        // vk::Queue video = VK_NULL_HANDLE;
        vk::Queue present = VK_NULL_HANDLE;
        vk::Queue graphics = VK_NULL_HANDLE;
        vk::Queue compute = VK_NULL_HANDLE;
        std::array<int32_t, 4>queueFamilies = {-1, -1, -1, -1};
        void CreateQueue(const Device&device);
        void CreateQueue(const Device&device, vk::SurfaceKHR surface);
    };
}
#endif