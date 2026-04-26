#ifndef VULKAN_BUFFER_HPP
#define VULKAN_BUFFER_HPP
#include "pool.hpp"
namespace vulkan{
    class Buffer{
        uint32_t count = 1;
        vk::DeviceSize size = 0;
        void *pMappedData = nullptr;
        vk::Buffer buffer = VK_NULL_HANDLE;
        vma::Allocation allocation;
        // vk::DeviceMemory memory = VK_NULL_HANDLE;
        vk::CommandBuffer BeginSingleTimeCommands(const Device&device, const Pool&pool);
        void EndSingleTimeCommands(vk::CommandBuffer command, vk::Queue queue, const Device&device, const Pool&pool);
    public:
        Buffer();
        ~Buffer();
        void Create(const Device&device, vk::DeviceSize size, vk::BufferUsageFlags usage, vma::MemoryUsage memoryUsage = vma::MemoryUsage::eAuto, bool keepMapped = false);
        void Create(const Device&device, vk::DeviceSize minUniformBufferOffset, uint32_t count, vk::BufferUsageFlags usage, vma::MemoryUsage memoryUsage, bool keepMapped = false);

        void Destroy(const Device&device);

        void PipelineBarrier(vk::CommandBuffer command, vk::PipelineStageFlags srcStageMask, vk::PipelineStageFlags dstStageMask, vk::AccessFlags srcAccessMask, vk::AccessFlags dstAccessMask);

        // void CreateBuffer(const Device&device, vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties);
        // void CreateBuffer(const Device&device, vk::DeviceSize minUniformBufferOffset, uint32_t count, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties);

        void UpdateData(const Device&device, const void *pData, vk::Queue queue, const Pool&pool);
        void UpdateData(const Device&device, const vulkan::Buffer&buffer, vk::Queue queue, const Pool&pool);

        void UpdateData(const Device&device, const void * pData, vk::DeviceSize offset = 0);
        void UpdateData(const Device&device, vk::DeviceSize size, const void * pData, vk::DeviceSize offset = 0);

        inline void FlushMappedMemoryRanges(const Device&device, vk::DeviceSize offset = 0)const{
            vma::Allocator allocator = device.GetAllocator();
            allocator.flushAllocation(allocation, offset, VK_WHOLE_SIZE);
        }
        inline operator vk::Buffer() const noexcept{
            return buffer;
        }
        inline bool operator==(vk::Buffer buf)const noexcept{
            return buffer == buf;
        }
        inline bool operator!=(vk::Buffer buf)const noexcept{
            return buffer != buf;
        }
        inline auto GetSize()const noexcept{
            return size;
        }
        inline auto&GetBuffer()const noexcept{
            return buffer;
        }
        inline void *MapMemory(const Device&device)const{
            vma::Allocator allocator = device.GetAllocator();
            return allocator.mapMemory(allocation);
        }
        inline void UnMapMemory(const Device&device)const{
            vma::Allocator allocator = device.GetAllocator();
            allocator.unmapMemory(allocation);
        }
    };    
}
#endif