#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP
#include "image.hpp"
namespace vulkan{
    class Swapchain{
        vk::Extent2D extent;
        std::vector<Image>images;
        vk::SwapchainKHR swapchain;
        vk::SurfaceFormatKHR surfaceFormat;
    public:
        Swapchain();
        ~Swapchain();
        inline operator vk::SwapchainKHR() const noexcept{
            return swapchain;
}
        void Create(const Device&device, vk::SurfaceKHR surface, uint32_t width, uint32_t height);

        void Cleanup(const Device&device);

        inline auto&GetExtent()const noexcept{
            return extent;
        }
        inline uint32_t GetImageSize()const noexcept{
            return images.size();
        }
        inline auto&GetSurfaceFormat()const noexcept{
            return surfaceFormat.format;
        }
        inline auto&GetImage(uint32_t index)noexcept{
            return index < images.size()?images[index]:images[0];
        }
    };
}
#endif