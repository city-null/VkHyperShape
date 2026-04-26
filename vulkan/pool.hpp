#ifndef VULKAN_POOL_HPP
#define VULKAN_POOL_HPP
#include "device.hpp"
namespace vulkan{
    class Pool{
        vk::CommandPool command;
        vk::DescriptorPool descriptor;
    public:
        void Cleanup(vk::Device device);
        void CreatePool(const Device&device, uint32_t descriptorCount, vk::CommandPoolCreateFlags flags);

        inline auto AllocateDescriptorSets(vk::Device device, const std::vector<vk::DescriptorSetLayout>&setlayout)const{
            vk::DescriptorSetAllocateInfo info = {};
            info.sType = vk::StructureType::eDescriptorSetAllocateInfo;
            info.descriptorPool = descriptor;
            info.pSetLayouts = setlayout.data();
            info.descriptorSetCount = setlayout.size();
            return device.allocateDescriptorSets(info);
        }
        inline auto AllocateCommandBuffers(vk::Device device, uint32_t count, vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary)const{
            vk::CommandBufferAllocateInfo info = {};
            info.sType = vk::StructureType::eCommandBufferAllocateInfo;
            info.level = level;
            info.commandPool = command;
            info.commandBufferCount = count;
            return device.allocateCommandBuffers(info);
        }
        inline auto AllocateCommandBuffers(vk::Device device, vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary)const{
            return AllocateCommandBuffers(device, 1, level)[0];
        }
        inline void FreeCommandBuffers(vk::Device device, vk::CommandBuffer command)const noexcept{
            device.freeCommandBuffers(this->command, command);
        }
        inline void FreeCommandBuffers(vk::Device device, const std::vector<vk::CommandBuffer>&command)const noexcept{
            device.freeCommandBuffers(this->command, command);
        }
        inline auto GetCommandPool()const noexcept{
            return command;
        }
    };
}
#endif