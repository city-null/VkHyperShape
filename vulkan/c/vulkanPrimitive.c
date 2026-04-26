#include "vulkanPrimitive.h"
VulkanPrimitive::VulkanPrimitive(){
    
}
VulkanPrimitive::~VulkanPrimitive(){

}

VkResult VulkanPrimitive::CreateIndexBuffer(VulkanDevice device, const void *data, VkDeviceSize size, VkQueue graphics, VulkanPool pool, VkIndexType indexType){
    this->indexType = indexType;
    indexCount = static_cast<uint32_t>(indexType == VK_INDEX_TYPE_UINT16?size / sizeof(uint16_t):size / sizeof(uint32_t));
    VkResult result = index.CreateBuffer(device, size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT,  VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (result == VK_SUCCESS) {
        index.UpdateData(device, data, graphics, pool);
    }
    return result;
}

VkResult VulkanPrimitive::CreateVertexBuffer(VulkanDevice device, const void *data, VkDeviceSize size, uint32_t vertexCount, VkQueue graphics, VulkanPool pool, VkBufferUsageFlags additionalUsage){
    this->vertexCount = vertexCount;
    VkResult result = vertex.CreateBuffer(device, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT|VK_BUFFER_USAGE_TRANSFER_DST_BIT|additionalUsage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (result == VK_SUCCESS) {
        vertex.UpdateData(device, data, graphics, pool);
    }
    return result;
}

void VulkanPrimitive::Destroy(VkDevice device){
    indexCount = 0;
    vertexCount = 0;
    index.Destroy(device);
    vertex.Destroy(device);
}

void VulkanPrimitive::Bind(VkCommandBuffer command) const{
    VkDeviceSize offset = 0;
    if(vertex.buffer != VK_NULL_HANDLE)vkCmdBindVertexBuffers(command, 0, 1, &vertex.buffer, &offset);
    if(index.buffer != VK_NULL_HANDLE)vkCmdBindIndexBuffer(command, index.buffer, offset, indexType);
}

void VulkanPrimitive::Bind(VkCommandBuffer command, VkIndexType indexType) const{
    VkDeviceSize offset = 0;
    if(vertex.buffer != VK_NULL_HANDLE)vkCmdBindVertexBuffers(command, 0, 1, &vertex.buffer, &offset);
    if(index.buffer != VK_NULL_HANDLE)vkCmdBindIndexBuffer(command, index.buffer, offset, indexType);
}

void VulkanPrimitive::Draw(VkCommandBuffer command, uint32_t vertexOffset, uint32_t firstIndex) const{
    if(index.buffer != VK_NULL_HANDLE){
        vkCmdDrawIndexed(command, indexCount, 1, firstIndex, vertexOffset, 0);
    }
    else if(vertex.buffer != VK_NULL_HANDLE){
        vkCmdDraw(command, vertexCount, 1, vertexOffset, 0);
    }
}