#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H
#include "VulkanPool.h"
#include "VulkanDevice.h"
struct VULKAN_BUFFER{
    uint32_t count;
    VkBuffer buffer;
    VkDeviceSize size;
    void *pMappedData;
    VmaAllocation allocation;
};

typedef struct VULKAN_BUFFER VulkanBuffer;

VulkanBuffer vulkanCreateBuffer(const VulkanDevice *device, VkDeviceSize size, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);
VulkanBuffer vulkanCreateBufferDynamic(VulkanDevice device, VkDeviceSize minUniformBufferOffset, uint32_t count, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);

void DestroyBuffer(const VulkanDevice *device, VulkanBuffer *buffer);

//     void UpdateData(VulkanDevice device, const void *pData, VkQueue graphics, VulkanPool pool);

//     void UpdateData(VkDevice device, const void * pData, VkDeviceSize offset = 0);
//     void UpdateData(VkDevice device, VkDeviceSize size, const void * pData, VkDeviceSize offset = 0);
#endif