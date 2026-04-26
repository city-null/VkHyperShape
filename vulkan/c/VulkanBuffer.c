#include "VulkanBuffer.h"
VulkanBuffer vulkanCreateBuffer(VmaAllocator allocator, VkDeviceSize size, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage){
    VulkanBuffer buffer = {};
    buffer.size = size;
    buffer.count = 1;

    VkBufferCreateInfo bufInfo = {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};
    bufInfo.size  = size;
    bufInfo.usage = usage;
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = usage;
    // VmaAllocationInfo allocationInfo = {};
    // // allocInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT
    // //                 | VMA_ALLOCATION_CREATE_MAPPED_BIT; 
    // vmaCreateBuffer(allocator, &bufInfo, &allocInfo, &buffer, &buffer.allocation, &allocationInfo);
    //     if(keepMapped)buffer.pMappedData = allocationInfo.pMappedData;
    vmaCreateBuffer(allocator, &bufInfo, &allocInfo, &buffer, &buffer.allocation, VK_NULL_HANDLE);
    return buffer;
}

VulkanBuffer vulkanCreateBufferDynamic(VmaAllocator allocator, VkDeviceSize minUniformBufferOffset, uint32_t count, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage){
    VulkanBuffer buffer = vulkanCreateBuffer(allocator, minUniformBufferOffset * count, usage, memoryUsage);
    buffer.count = count;
    buffer.size = minUniformBufferOffset;
    return buffer;
}
// void VulkanBuffer::UpdateData(VulkanDevice device, const void *pData, VkQueue graphics, VulkanPool pool){
//     if(!pData || buffer == VK_NULL_HANDLE)return;
//     VulkanBuffer temporary;
//     temporary.CreateBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
//     temporary.UpdateData(device.device, size, pData);
//     VkCommandBuffer command;
//     VkBufferCopy regions = {};
//     regions.size = size;
//     pool.AllocateCommandBuffers(device.device, 1, &command);
// 	VkCommandBufferBeginInfo beginInfo = {};
// 	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
// 	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
// 	vkBeginCommandBuffer(command, &beginInfo);

//     vkCmdCopyBuffer(command, temporary.buffer, buffer, 1, &regions);

//     // Create fence to ensure that the command buffer has finished executing
//     VkFence fence;
//     VkFenceCreateInfo fenceInfo = {};
//     fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
//     vkCreateFence(device.device, &fenceInfo, nullptr, &fence);

// 	vkEndCommandBuffer(command);
    
// 	VkSubmitInfo submitInfo = {};
// 	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
// 	submitInfo.commandBufferCount = 1;
// 	submitInfo.pCommandBuffers = &command;

// 	vkQueueSubmit(graphics, 1, &submitInfo, fence);
    
//     // Wait for the fence to signal that command buffer has finished executing
//     vkWaitForFences(device.device, 1, &fence, VK_TRUE, UINT64_MAX);
//     vkDestroyFence(device.device, fence, nullptr);

// 	vkFreeCommandBuffers(device.device, pool.command, 1, &command);

//     temporary.Destroy(device.device);
// }

// void VulkanBuffer::UpdateData(VkDevice device, const void *pData, VkDeviceSize offset){
//     UpdateData(device, size, pData, offset);
// }

// void VulkanBuffer::UpdateData(VkDevice device, VkDeviceSize size, const void *pData, VkDeviceSize offset){
//     if(!pData || buffer == VK_NULL_HANDLE)return;
// 	void* data;
// 	vkMapMemory(device, memory, offset, size, 0, &data);
// 	memcpy(data, pData, size);
// 	vkUnmapMemory(device, memory);
// }

void DestroyBuffer(const VulkanDevice *device, VulkanBuffer *buffer){
    if(buffer->buffer != VK_NULL_HANDLE)vkDestroyBuffer(device, buffer, VK_NULL_HANDLE);
    if(buffer->allocation != VK_NULL_HANDLE)vmaDestroyBuffer(device->allocator, buffer->buffer, buffer->allocation);
    buffer = VK_NULL_HANDLE;
    buffer->allocation = VK_NULL_HANDLE;
}