#include "pool.hpp"
namespace vulkan{
    void Pool::Cleanup(vk::Device device){
        device.destroyCommandPool(command, nullptr);
        device.destroyDescriptorPool(descriptor, nullptr);
    }
    void Pool::CreatePool(const Device&device, uint32_t descriptorCount, vk::CommandPoolCreateFlags flags){
        vk::Device dev = device;
        vk::CommandPoolCreateInfo commandCreateInfo = {};
        uint32_t graphicsFamily = device.GetQueueFamiliesIndex(vk::QueueFlagBits::eGraphics);
        commandCreateInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
        commandCreateInfo.flags = flags;
        commandCreateInfo.queueFamilyIndex = graphicsFamily;
        command = dev.createCommandPool(commandCreateInfo);
        std::vector<vk::DescriptorPoolSize> descriptorPoolSize = {
            { vk::DescriptorType::eSampler, descriptorCount },
            {  vk::DescriptorType::eCombinedImageSampler, descriptorCount },
            { vk::DescriptorType::eSampledImage, descriptorCount },
            { vk::DescriptorType::eStorageImage, descriptorCount },
            { vk::DescriptorType::eUniformTexelBuffer, descriptorCount },
            { vk::DescriptorType::eStorageTexelBuffer, descriptorCount },
            { vk::DescriptorType::eUniformBuffer, descriptorCount },
            { vk::DescriptorType::eStorageBuffer, descriptorCount },
            { vk::DescriptorType::eUniformBufferDynamic, descriptorCount },
            { vk::DescriptorType::eStorageBufferDynamic, descriptorCount },
            { vk::DescriptorType::eInputAttachment, descriptorCount}
        };
        vk::DescriptorPoolCreateInfo info = {};
        info.sType = vk::StructureType::eDescriptorPoolCreateInfo;
        info.maxSets = descriptorCount;
        info.poolSizeCount = descriptorPoolSize.size();
        info.pPoolSizes = descriptorPoolSize.data();
        descriptor = dev.createDescriptorPool(info);
    }
}