#ifndef VULKAN_PRIMITIVE_HPP
#define VULKAN_PRIMITIVE_HPP
#include "buffer.hpp"
namespace vulkan{
    class Primitive{
        Buffer index;
        Buffer vertex;
        uint32_t indexCount = 0;
        uint32_t vertexCount = 0;
        vk::IndexType indexType = vk::IndexType::eUint16;
    public:
        void CreateVertexBuffer(const Device&device, vk::DeviceSize size, uint32_t vertexCount, bool hostvisible);
        void CreateIndexBuffer(const Device&device, vk::DeviceSize size, bool hostvisible, vk::IndexType indexType = vk::IndexType::eUint16);

        void CreateVertexBuffer(const Device&device, const void* data, vk::DeviceSize size, uint32_t vertexCount, vk::Queue graphics, const Pool&pool);
        void CreateIndexBuffer(const Device&device, const void* data, vk::DeviceSize size, vk::Queue graphics, const Pool&pool, vk::IndexType indexType = vk::IndexType::eUint16);

        void Bind(vk::CommandBuffer command)const noexcept;
        void Bind(vk::CommandBuffer command, vk::IndexType indexType)const noexcept;

        void Destroy(const Device&device);
        void Draw(vk::CommandBuffer command, uint32_t vertexOffset = 0, uint32_t firstIndex = 0)const noexcept;

        void FlushMappedMemoryRanges(const Device&device)const;

        // inline void DestroyVertex(vk::Device device){
        //     vertex.Destroy(device);
        //     vertexCount = 0;
        // }
        // inline void DestroyIndex(vk::Device device){
        //     index.Destroy(device);
        //     indexCount = 0;
        // }
        inline bool IsVaildIndex()const noexcept{
            return index != VK_NULL_HANDLE;
        }
        inline bool IsVaildVertex()const noexcept{
            return vertex != VK_NULL_HANDLE;
        }
        inline auto MapMemoryVertex(const Device&device)const{
            return vertex.MapMemory(device);
        }
        inline void UnMapMemoryVertex(const Device&device)const{
            vertex.UnMapMemory(device);
        }
        inline auto MapMemoryIndex(const Device&device)const{
            return index.MapMemory(device);
        }
        inline void UnMapMemoryIndex(const Device&device)const{
            index.UnMapMemory(device);
        }
        inline void UpdateVertexData(const Device&device, const void* data, vk::DeviceSize size){
            vertex.UpdateData(device, size, data);
        }
        //至少得执行过一次CreateVertexBuffer才能调用该函数
        inline void UpdateVertexData(const Device&device, const void* data){
            UpdateVertexData(device, data, vertex.GetSize());
        }
        inline void UpdateVertexData(const Device&device, const void* data, vk::Queue graphics, const vulkan::Pool&pool){
            vertex.UpdateData(device, data, graphics, pool);
        }
        inline void UpdateIndexData(const Device&device, const void* data, vk::DeviceSize size){
            index.UpdateData(device, size, data);
        }
        //至少得执行过一次CreateIndexBuffer才能调用该函数
        inline void UpdateIndexData(const Device&device, const void* data){
            UpdateIndexData(device, data, index.GetSize());
        }
        inline void UpdateIndexData(const Device&device, const void* data, vk::Queue graphics, const vulkan::Pool&pool){
            index.UpdateData(device, data, graphics, pool);
        }
        inline void SetIndexCount(uint32_t count)noexcept{
            indexCount = count;
        }
        inline void SetVertexCount(uint32_t count)noexcept{
            vertexCount = count;
        }
        inline uint32_t GetIndexCount()const noexcept{
            return indexCount;
        }
        inline uint32_t GetVertexCount()const noexcept{
            return vertexCount;
        }
        inline uint32_t GetVertexSize()const noexcept{
            return vertex.GetSize();
        }
        inline uint32_t GetIndexSize()const noexcept{
            return index.GetSize();
        }
        inline auto GetVertex()const noexcept{
            return vertex.GetBuffer();
        }
        inline auto GetIndex()const noexcept{
            return index.GetBuffer();
        }
    };
}
#endif